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

#include <OSGConfig.h>

#include <GL/gl.h>

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

char DynamicBackground::cvsid[] = "@(#)$Id: OSGDynamicBackground.cpp,v 1.7 2001/10/05 04:17:43 vossg Exp $";

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

void DynamicBackground::addColor( Color3f col, Real32 pos )
{
	if ( _mfAngle.getSize() < 1 )
	{
		_mfColor.addValue( col );
		_mfAngle.addValue( pos );
	}
	else 
	{
		if ( pos < _mfAngle.getValue(_mfAngle.getSize() - 1) )
		{
			_mfColor.addValue( col );
			_mfAngle.addValue( pos );
		}
		else
		{
			_mfAngle.addValue( _mfAngle.getValue(_mfAngle.getSize() - 1) );
			_mfColor.addValue( _mfColor.getValue(_mfColor.getSize() - 1) );

			for (int i = _mfAngle.getSize() - 1 ; i > 0 ; i--)
			{				
				_mfAngle.setValue( _mfAngle.getValue(i - 1), i);
				_mfColor.setValue( _mfColor.getValue(i - 1), i);
				
				if ( pos < _mfAngle.getValue(i) )
				{
					_mfColor.setValue( col, i );
					_mfAngle.setValue( pos, i );
					break;
				}
			}
		}

		if ( pos >= _mfAngle.getValue(0) )
		{
			_mfAngle.setValue( pos, 0 );
			_mfColor.setValue( col, 0 );
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

void DynamicBackground::clear(DrawActionBase *action, ViewportP viewport)
{
	if (_mfAngle.getSize() < 2)
	{
		if (_mfAngle.getSize() == 1)
		{
			Color3f col = _mfColor.getValue( 0 );
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

		Bool light = glIsEnabled(GL_LIGHTING);
		if (light)	glDisable(GL_LIGHTING);

		GLint fill;
		glGetIntegerv(GL_POLYGON_MODE, &fill);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

		GLint depth;
		glGetIntegerv(GL_DEPTH_FUNC, &depth);
		glDepthFunc(GL_ALWAYS);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		action->getCamera()->getViewing( m, viewport->getPixelWidth(),
		    	    	    				viewport->getPixelHeight() );
		m[3][0] = m[3][1] = m[3][2] = 0;
		glLoadMatrixf( m.getValues() );		
		float scale = ( action->getCamera()->getFar() + 
						action->getCamera()->getNear() ) / 2;
		glScalef( scale, scale, scale );

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();

		action->getCamera()->getProjection( m, viewport->getPixelWidth(),
		    	    	    				   viewport->getPixelHeight() );
		glLoadMatrixf( m.getValues() );		
		
		Real32 r1, g1, b1, r2, g2, b2;
		Real32 pos;
		UInt32 size = _mfAngle.getSize();
		Real32 sin1, sin2, cos1, cos2, ank1, ank2;
		Color3f col1, col2;

		// ignore values bigger than 1 and lower 0

		int first;
		int j;
		for ( j = 0 ; j < size ; j++ )
		{
			if ( _mfAngle.getValue( j ) <= 1 )
			{
				first = j;
				break;
			}
		}
	
		int last;
		for ( j = size - 1 ; j >= 0 ; j--)
		{
			if ( _mfAngle.getValue( j ) >= 0 )
			{
				last = j + 1;
				break;
			}
		}

		// lower pole

	
		if (_mfAngle.getValue(first) == 1) 
		{
			col1 = _mfColor.getValue(first);
			col1.getValuesRGB(r1, g1, b1);
			col2 = _mfColor.getValue(first + 1);
			col2.getValuesRGB(r2, g2, b2);
			pos = _mfAngle.getValue(first + 1);

		}
		else 
		{
			r1 = 0.0;
			g1 = 0.0;
			b1 = 0.0;
			col2 = _mfColor.getValue(first);
			col2.getValuesRGB(r2, g2, b2);
			pos = _mfAngle.getValue(first);
		}

		sin2 = sin( pos * Pi );
		cos2 = -cos( pos * Pi );
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

		// upper pole

		if (_mfAngle.getValue(last - 1) == 0) 
		{
			col1 = _mfColor.getValue(last - 1);
			col1.getValuesRGB(r1, g1, b1);
			col2 = _mfColor.getValue(last - 2);
			col2.getValuesRGB(r2, g2, b2);
			pos = _mfAngle.getValue(last - 2);
			last = last - 1;
		}
		else 
		{
			r1 = 0.0;
			g1 = 0.0;
			b1 = 0.0;
			col2 = _mfColor.getValue(last - 1);
			col2.getValuesRGB(r2, g2, b2);
			pos = _mfAngle.getValue(last - 1);
		}

		cos2 = -cos( pos * Pi );
		sin2 = sin( pos * Pi );
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

		for( int i = first; i < last - 1; i++)
		{
			
			Real32 pos1 = _mfAngle.getValue(i);
			Real32 pos2 = _mfAngle.getValue(i + 1);
			sin1 = sin( pos1 * Pi );
			sin2 = sin( pos2 * Pi );
			ank1 = cos(Pi / 4) * sin1;
			cos1 = -cos( pos1 * Pi );
			cos2 = -cos( pos2 * Pi );
			ank2 = cos(Pi / 4) * sin2;

		
			col1 = _mfColor.getValue(i);
			col2 = _mfColor.getValue(i + 1);
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

