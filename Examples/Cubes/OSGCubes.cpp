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


#define OSG_COMPILEMYLIB

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <OpenSG/OSGGL.h>


#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGDrawAction.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGState.h>
#include <OpenSG/OSGMaterial.h>

#include "OSGCubes.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Cubes

A test node for directly rendering to OpenGL.


*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Cubes::cvsid[] = "@(#)$Id: $";

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

void Cubes::initMethod (void)
{
    DrawAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::drawActionHandler));
  
    RenderAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::renderActionHandler));
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

Cubes::Cubes(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

Cubes::Cubes(const Cubes &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

Cubes::~Cubes(void)
{
}


/** \brief react to field changes
 */

void Cubes::changed(BitVector, UInt32)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void Cubes::dump(      UInt32     uiIndent, 
                         const BitVector bvFlags) const
{
    SLOG << "Dump Cubes NI" << std::endl;
}

    
Action::ResultE Cubes::drawPrimitives(DrawActionBase * action )
{
    if ( getMFPosition()->size() != getMFLength()->size() ||
         getMFPosition()->size() != getMFColor()->size() )
    {
        SWARNING << "Cubes::draw: inconsistent attributes!" << std::endl;
        return Action::Continue;
    }

    // some variables for faster access
    MFPnt3f   *pos = getMFPosition();
    MFColor3f *col = getMFColor();
    MFReal32  *len = getMFLength();
    
    glBegin( GL_QUADS );
    
    // draw the cubes
    for ( UInt32 i = 0; i < pos->size(); i++ )
    {
        glColor3fv( (GLfloat*) &((*col)[i]) );
        
        Pnt3f  p = (*pos)[i];       
        Real32 l = (*len)[i] / 2.f;
        
        glNormal3f( 0, 0, -1 );
        glVertex3f( p[0] - l, p[1] - l, p[2] - l );
        glVertex3f( p[0] + l, p[1] - l, p[2] - l );
        glVertex3f( p[0] + l, p[1] + l, p[2] - l );
        glVertex3f( p[0] - l, p[1] + l, p[2] - l );
        
        glNormal3f( 0, 0, 1 );
        glVertex3f( p[0] - l, p[1] - l, p[2] + l );
        glVertex3f( p[0] + l, p[1] - l, p[2] + l );
        glVertex3f( p[0] + l, p[1] + l, p[2] + l );
        glVertex3f( p[0] - l, p[1] + l, p[2] + l );
        
        glNormal3f( -1, 0, 0 );
        glVertex3f( p[0] - l, p[1] - l, p[2] - l );
        glVertex3f( p[0] - l, p[1] - l, p[2] + l );
        glVertex3f( p[0] - l, p[1] + l, p[2] + l );
        glVertex3f( p[0] - l, p[1] + l, p[2] - l );
        
        glNormal3f( 1, 0, 0 );
        glVertex3f( p[0] + l, p[1] - l, p[2] + l );
        glVertex3f( p[0] + l, p[1] - l, p[2] - l );
        glVertex3f( p[0] + l, p[1] + l, p[2] - l );
        glVertex3f( p[0] + l, p[1] + l, p[2] + l );
        
        glNormal3f( 0, 1, 0 );
        glVertex3f( p[0] - l, p[1] + l, p[2] + l );
        glVertex3f( p[0] + l, p[1] + l, p[2] + l );
        glVertex3f( p[0] + l, p[1] + l, p[2] - l );
        glVertex3f( p[0] - l, p[1] + l, p[2] - l );
        
        glNormal3f( 0, -1, 0 );
        glVertex3f( p[0] - l, p[1] - l, p[2] - l );
        glVertex3f( p[0] + l, p[1] - l, p[2] - l );
        glVertex3f( p[0] + l, p[1] - l, p[2] + l );
        glVertex3f( p[0] - l, p[1] - l, p[2] + l );
    }
    
    glEnd();
    
    return Action::Continue;
}


void Cubes::adjustVolume( Volume & volume )
{   
    volume.setValid();
    volume.setEmpty();

    MFPnt3f   *pos = getMFPosition();
    MFReal32  *len = getMFLength();
    
    // go through all the cubes adjusting the volume
    for ( int i = 0; i < pos->size(); i++ )
    {
        Pnt3f center = (*pos)[i];
        
        Real32 l = (*len)[i] / 2;
        
        // create the corners of the cube
        for ( Int16 z = -1; z <= 1; z += 2 )
        for ( Int16 y = -1; y <= 1; y += 2 )
        for ( Int16 x = -1; x <= 1; x += 2 )
            volume.extendBy( Pnt3f( center[0] + x * l, 
                                    center[1] + y * l, 
                                    center[2] + z * l )  );
    }
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

