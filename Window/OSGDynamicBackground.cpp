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

#include <OSGDrawAction.h>

#include "OSGCamera.h"
#include "OSGViewport.h"

#include "OSGDynamicBackground.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DynamicBackground

A sky-sphere background showing a color gradient. The colors and angles correspond to  each other, they should have the same number of elements. 	

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char DynamicBackground::cvsid[] = "@(#)$Id: OSGDynamicBackground.cpp,v 1.1 2001/04/15 02:19:06 dirk Exp $";

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

void DynamicBackground::initMethod (void)
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

DynamicBackground::DynamicBackground(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

DynamicBackground::DynamicBackground(const DynamicBackground &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

DynamicBackground::~DynamicBackground(void)
{
}


/** \brief react to field changes
 */

void DynamicBackground::changed(BitVector, ChangeMode)
{
}

/*------------------------------ access -----------------------------------*/

void DynamicBackground::addColors( Color3f col, Real32 pos )
{
	if ( _angle.getSize() < 1 )
	{
		_color.addValue( col );
		_angle.addValue( pos );
	}
	else 
	{
		if ( pos < _angle.getValue(_angle.getSize() - 1) )
		{
			_color.addValue( col );
			_angle.addValue( pos );
		}
		else
		{
			_angle.addValue( _angle.getValue(_angle.getSize() - 1) );
			_color.addValue( _color.getValue(_color.getSize() - 1) );

			for (int i = _angle.getSize() - 1 ; i > 0 ; i--)
			{				
				_angle.setValue( _angle.getValue(i - 1), i);
				_color.setValue( _color.getValue(i - 1), i);
				
				if ( pos < _angle.getValue(i) )
				{
					_color.setValue( col, i );
					_angle.setValue( pos, i );
					i = 0;
				}
			}
		}

		if ( pos >= _angle.getValue(0) )
		{
			_angle.setValue( pos, 0 );
			_color.setValue( col, 0 );
		}
	}
}


/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void DynamicBackground::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
	SLOG << "Dump DynamicBackground NI" << endl;
}

/*-------------------------- your_category---------------------------------*/

void DynamicBackground::clear(DrawAction *action, ViewportP viewport)
{
	if (_angle.getSize() < 2)
	{
		if (_angle.getSize() == 1)
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
		Matrix m;

		bool light = glIsEnabled(GL_LIGHTING);
		if (light)	glDisable(GL_LIGHTING);

		GLint fill;
		glGetIntegerv(GL_POLYGON_MODE, &fill);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

		GLint depth;
		glGetIntegerv(GL_DEPTH_FUNC, &depth);
		glDepthFunc(GL_ALWAYS);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		action->getCamera()->getViewing( m, *viewport );
		m[3][0] = m[3][1] = m[3][2] = 0;
		glLoadMatrixf( m.getValues() );		

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		action->getCamera()->getProjection( m, *viewport );
		glLoadMatrixf( m.getValues() );		
		
		Real32 r1, g1, b1, r2, g2, b2;
		Real32 pos;
//		UInt32 size = _angle.getSize();
		Real32 sin1, sin2, cos1, cos2, ank1, ank2;
		Color3f col1, col2;

// ignore values bigger than 180 and lower 0

	int z;
	int j;
	for ( j = 0 ; j < _angle.getSize() ; j++ )
	{
		if ( _angle.getValue( j ) <= 180 )
		{
			z = j;
			break;
		}
	}

	int size;
	for ( j = _angle.getSize() - 1 ; j >= 0 ; j--)
	{
		if ( _angle.getValue( j ) >= 0 )
		{
			size = j + 1;
			break;
		}
	}

// lower pole

	
		if (_angle.getValue(z) == 180) 
		{
			col1 = _color.getValue(z);
			col1.getValuesRGB(r1, g1, b1);
			col2 = _color.getValue(z + 1);
			col2.getValuesRGB(r2, g2, b2);
			pos = _angle.getValue(z + 1);
//			z++;

		}
		else 
		{
			r1 = 0.0;
			g1 = 0.0;
			b1 = 0.0;
			col2 = _color.getValue(z);
			col2.getValuesRGB(r2, g2, b2);
			pos = _angle.getValue(z);
		}

		sin2 = sin((pos * 2 * Pi) / 360);
		cos2 = cos((pos * 2 * Pi) / 360);
		ank2 = cos(Pi / 4) * sin2;


		glBegin(GL_TRIANGLE_FAN);
			glColor3f( r1, g1, b1);
			glVertex3f(0, -1, 0);
			glColor3f( r2, g2, b2);
			glVertex3f(sin2, cos2, 0);
			glVertex3f(ank2, cos2, ank2);
			glVertex3f(0, cos2, sin2);
			glVertex3f(-ank2, cos2, ank2);
			glVertex3f(-sin2, cos2, 0);
			glVertex3f(-ank2, cos2, -ank2);
			glVertex3f(0, cos2, -sin2);
			glVertex3f(ank2, cos2, -ank2);
			glVertex3f(sin2, cos2, 0);
		glEnd();

// upper pole

		if (_angle.getValue(size - 1) == 0) 
		{
			col1 = _color.getValue(size - 1);
			col1.getValuesRGB(r1, g1, b1);
			col2 = _color.getValue(size - 2);
			col2.getValuesRGB(r2, g2, b2);
			pos = _angle.getValue(size - 2);
			size = size - 1;
		}
		else 
		{
			r1 = 0.0;
			g1 = 0.0;
			b1 = 0.0;
			col2 = _color.getValue(size - 1);
			col2.getValuesRGB(r2, g2, b2);
			pos = _angle.getValue(size - 1);
		}

		cos2 = cos((pos * 2 * Pi) / 360);
		sin2 = sin((pos * 2 * Pi) / 360);
		ank2 = cos(Pi / 4) * sin2;

		
		glBegin(GL_TRIANGLE_FAN);
			glColor3f( r1, g1, b1);
			glVertex3f(0, 1, 0);
			glColor3f( r2, g2, b2);
			glVertex3f(sin2, cos2, 0);
			glVertex3f(ank2, cos2, ank2);
			glVertex3f(0, cos2, sin2);
			glVertex3f(-ank2, cos2, ank2);
			glVertex3f(-sin2, cos2, 0);
			glVertex3f(-ank2, cos2, -ank2);
			glVertex3f(0, cos2, -sin2);
			glVertex3f(ank2, cos2, -ank2);
			glVertex3f(sin2, cos2, 0);
		glEnd();
	
// midle

		for( int i = z; i < size - 1; i++)
		{
			
			Real32 pos1 = _angle.getValue(i);
			Real32 pos2 = _angle.getValue(i + 1);
			sin1 = sin((pos1 * 2 * Pi) / 360);
			sin2 = sin((pos2 * 2 * Pi) / 360);
			ank1 = cos(Pi / 4) * sin1;
			cos1 = cos((pos1 * 2 * Pi) / 360);
			cos2 = cos((pos2 * 2 * Pi) / 360);
			ank2 = cos(Pi / 4) * sin2;

		
			col1 = _color.getValue(i);
			col2 = _color.getValue(i + 1);
			col1.getValuesRGB(r1, g1, b1);
			col2.getValuesRGB(r2, g2, b2);

			glBegin(GL_TRIANGLE_STRIP);
				glColor3f( r1, g1, b1);
				glVertex3f(sin1, cos1, 0);
				glColor3f( r2, g2, b2);
				glVertex3f(sin2, cos2, 0);

				glColor3f( r1, g1, b1);
				glVertex3f(ank1, cos1, ank1);
				glColor3f( r2, g2, b2);
				glVertex3f(ank2, cos2, ank2);

				glColor3f( r1, g1, b1);
				glVertex3f(0, cos1, sin1);
				glColor3f( r2, g2, b2);
				glVertex3f(0, cos2, sin2);

				glColor3f( r1, g1, b1);
				glVertex3f(-ank1, cos1, ank1);
				glColor3f( r2, g2, b2);
				glVertex3f(-ank2, cos2, ank2);
				
				glColor3f( r1, g1, b1);				
				glVertex3f(-sin1, cos1, 0);
				glColor3f( r2, g2, b2);
				glVertex3f(-sin2, cos2, 0);

				glColor3f( r1, g1, b1);
				glVertex3f(-ank1, cos1, -ank1);
				glColor3f( r2, g2, b2);
				glVertex3f(-ank2, cos2, -ank2);
		
				glColor3f( r1, g1, b1);
				glVertex3f(0, cos1, -sin1);
				glColor3f( r2, g2, b2);
				glVertex3f(0, cos2, -sin2);

				glColor3f( r1, g1, b1);
				glVertex3f(ank1, cos1, -ank1);
				glColor3f( r2, g2, b2);
				glVertex3f(ank2, cos2, -ank2);

				glColor3f( r1, g1, b1);				
				glVertex3f(sin1, cos1, 0);
				glColor3f( r2, g2, b2);
				glVertex3f(sin2, cos2, 0);
			glEnd();
		}
	
		
		glClear( GL_DEPTH_BUFFER_BIT );

		glPopMatrix();
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		glDepthFunc(depth);
		glPolygonMode( GL_FRONT_AND_BACK, fill);
		if (light)	glEnable(GL_LIGHTING);
		glColor3f(1.0, 1.0, 1.0);
	}
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

