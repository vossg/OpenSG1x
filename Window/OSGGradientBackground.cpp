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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGGL.h>

#include <OSGFieldContainer.h>
#include <OSGNode.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGBackground.h"
#include "OSGGradientBackground.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GradientBackground
    \ingroup Backgrounds

A background showing a vertical color gradient. The colors and positions correspond to each other, so both have to have the same number of elements.    

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char GradientBackground::cvsid[] = "@(#)$Id: OSGGradientBackground.cpp,v 1.20 2002/07/02 15:13:51 dirk Exp $";

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

void GradientBackground::initMethod (void)
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

GradientBackground::GradientBackground(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

GradientBackground::GradientBackground(const GradientBackground &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

GradientBackground::~GradientBackground(void)
{
}


/** \brief react to field changes
 */

void GradientBackground::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*-------------------------- your_category---------------------------------*/

void GradientBackground::clear(DrawActionBase *, Viewport *)
{

    if (_mfPosition.size() < 2)
    {
        if (_mfPosition.size() == 1)
        {
            Color3f col = _mfColor[0];
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
        if (light)  glDisable(GL_LIGHTING);

        GLint fill[2];
        glGetIntegerv(GL_POLYGON_MODE, fill);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
        UInt32 size = _mfPosition.size();

        glBegin( GL_QUAD_STRIP );
        
        Real32 pos = _mfPosition[0];
        if ( pos > 0 ) 
        {
            glColor3f( 0.0, 0.0, 0.0);
            glVertex3f(0, 0, 0);
            glVertex3f(1, 0, 0);
        }

        for( UInt32 i = 0; i < size; i++)
        {
            pos = _mfPosition[i];

            Color3f col1 = _mfColor[i];
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

        if ( depth )    glEnable( GL_DEPTH_TEST );
        if ( light )    glEnable( GL_LIGHTING );
        if ( colmat )   glEnable( GL_COLOR_MATERIAL );
        glPolygonMode( GL_FRONT, fill[0] );
        glPolygonMode( GL_BACK , fill[1] );

        glClear( GL_DEPTH_BUFFER_BIT );
    }
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void GradientBackground::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                              const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump GradientBackground NI" << endl;
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

