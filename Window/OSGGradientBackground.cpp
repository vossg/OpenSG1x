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
#include "OSGGradientBackground.h"

/** \enum VecBase::VectorSizeE
 *  \brief 
 */

/** \var VecBase::VectorSizeE VecBase::_iSize
 * 
 */

/** \fn const char *VecBase::getBackground(void)
 *  \brief Background
 */

/** \var ValueTypeT VecBase::_values[iSize];
 *  \brief Value store
 */

using namespace osg;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

//#pragma instantiate SField<GradientBackgroundPtr>::_fieldType
#pragma instantiate MField<GradientBackgroundPtr>::_fieldType

#else

//OSG_DLLEXPORT_DEF1(SField, GradientBackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, GradientBackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char GradientBackground::cvsid[] = "@(#)$Id: OSGGradientBackground.cpp,v 1.1 2001/02/12 01:26:33 dirk Exp $";

OSG_FC_FIRST_FIELD_IDM_DEF(GradientBackground, ColorField)
OSG_FC_FIELD_IDM_DEF      (GradientBackground, PositionField, ColorField)
OSG_FC_LAST_FIELD_IDM_DEF (GradientBackground, PositionField)

// Static Class Varible implementations: 
FieldDescription GradientBackground::_desc[] = 
{
        FieldDescription( MFColor3f::getClassType(), 
                            "color", 
                            OSG_FC_FIELD_IDM_DESC(ColorField),
                            false,
                            (FieldAccessMethod) &GradientBackground::getMFColor),

		FieldDescription( MFReal32::getClassType(), 
							"x", 
							OSG_FC_FIELD_IDM_DESC(PositionField),
							false,           
							(FieldAccessMethod) &GradientBackground::getMFPosition),
};

FieldContainerType GradientBackground::_type(
    "GradientBackground", 
    "FieldContainer", 
    0,
    (PrototypeCreateF) &GradientBackground::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(GradientBackground, GradientBackgroundPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

 GradientBackground::GradientBackground(void) 
//:
//	Inherited()
// TODO: initialize members
{
}

/** \copy Constructor
 */
GradientBackground::GradientBackground(const GradientBackground &source) 
{
	this->setMFColor( source._color );
	this->setMFPosition( source._position );	
}

/** \brief Destructor
 */

GradientBackground::~GradientBackground(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void GradientBackground::clear(DrawAction *, ViewportP)
{

	if (_position.getSize() < 2)
	{
		if (_position.getSize() == 1)
		{
			Color3f col = _color.getValue( 0 );
			Real32 r, g, b;
			col.getValuesRGB(r, g, b);
			glClearColor( r, g, b, 1);
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		}
		else
		{
			glClearColor( 0, 0, 0, 1);
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		}
	}
	else
	{
		bool light = glIsEnabled(GL_LIGHTING);
		if (light)	glDisable(GL_LIGHTING);

		GLint fill;
		glGetIntegerv(GL_POLYGON_MODE, &fill);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

		bool depth = glIsEnabled( GL_DEPTH_TEST );
		glDisable( GL_DEPTH_TEST );

		bool colmat = glIsEnabled( GL_COLOR_MATERIAL );
		glDisable( GL_COLOR_MATERIAL );

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, 1, 0, 1, 0, 1);

		Real32 r1, g1, b1;
		UInt32 size = _position.getSize();

		glBegin( GL_QUAD_STRIP );
		
		Real32 pos = _position.getValue(0);
		if ( pos > 0 ) 
		{
			glColor3f( 0.0, 0.0, 0.0);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);
		}

		for( int i = 0; i < size; i++)
		{
			pos = _position.getValue(i);

			Color3f col1 = _color.getValue(i);
			col1.getValuesRGB(r1, g1, b1);

			glColor3f( r1, g1, b1);
			glVertex3f(0, pos, 0);
			glVertex3f(1, pos, 0);
		}

		if ( pos < 1 ) 
		{
			glColor3f( 0.0, 0.0, 0.0);
			glVertex3f(0, 1, 0);
			glVertex3f(1, 1, 0);
		}
		
		glEnd();

		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		if ( depth )	glEnable( GL_DEPTH_TEST );
		if ( light )	glEnable( GL_LIGHTING );
		if ( colmat )	glEnable( GL_COLOR_MATERIAL );
		glPolygonMode( GL_FRONT_AND_BACK, fill );

		glClear( GL_DEPTH_BUFFER_BIT );
	}
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

GradientBackground &GradientBackground::operator = (const GradientBackground &source)
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

void GradientBackground::dump(void) const
{
    SDEBUG << "Dump GradientBackground NI" << endl;
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

