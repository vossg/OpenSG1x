/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <OSGGL.h>

#include <OSGFieldContainer.h>
#include <OSGNode.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"

#include "OSGImageForeground.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ImageForeground
    \ingroup GrpSystemWindowForegrounds

Background is the base class for all background clearing.       

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char ImageForeground::cvsid[] = "@(#)$Id: OSGImageForeground.cpp,v 1.6 2001/11/01 09:03:30 vossg Exp $";

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

void ImageForeground::initMethod (void)
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

ImageForeground::ImageForeground(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

ImageForeground::ImageForeground(const ImageForeground &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

ImageForeground::~ImageForeground(void)
{
}


/** \brief react to field changes
 */

void ImageForeground::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void ImageForeground::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                           const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump ImageForeground NI" << std::endl;
}


/** \brief draw the images 
 */
    
void ImageForeground::draw(DrawActionBase *, Viewport *)
{
    UInt16 i;
    
    for(i = 0; i < getPositions().size(); i++)
    {
        if(getImages(i) != NULL)
            break;;
    }
    
    if(i == getPositions().size())   // all images == NULL?
        return; 
        
    bool light = glIsEnabled(GL_LIGHTING);
//      if (light)  glDisable(GL_LIGHTING);

    GLint fill[2];
    glGetIntegerv(GL_POLYGON_MODE, fill);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

    bool depth = glIsEnabled( GL_DEPTH_TEST );
    glDisable( GL_DEPTH_TEST );

    bool colmat = glIsEnabled( GL_COLOR_MATERIAL );
    glDisable( GL_COLOR_MATERIAL );

    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);

    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_BLEND );

    for(i = 0; i < getPositions().size(); i++)
    {
        ImageP img = getImages( i );

        if ( ! img )
            continue;

        Pnt2f p = getPositions( i );
        glRasterPos2f( p[0], p[1] );
        glDrawPixels( img->getWidth(), img->getHeight(),
                      img->getPixelFormat(), GL_UNSIGNED_BYTE,
                      img->getData() );
    }
    glDisable( GL_BLEND );
        

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    if ( depth )    glEnable( GL_DEPTH_TEST );
    if ( light )    glEnable( GL_LIGHTING );
    if ( colmat )   glEnable( GL_COLOR_MATERIAL );
    glPolygonMode( GL_FRONT, fill[0] );
    glPolygonMode( GL_BACK , fill[1] );
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



