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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <GL/gl.h>

#define OSG_COMPILELIGHT

#include "OSGLightBase.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LightBase
 *	\defgroup LightNodes
 *	\ingroup NodesLib
 *  LightBase is the base class for all the light source nodes.
 *  It contains the field for the general light source attributes 
 *  (AmbientColor, DiffuseColor, SpecularColor, Beacon). The Beacon 
 *  defines the reference coordinate system for the lightsource, while 
 *  the position in the graph defines the objects that are lit.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char LightBase::cvsid[] = "@(#)$Id: $";

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

void LightBase::initMethod (void)
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

LightBase::LightBase(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

LightBase::LightBase(const LightBase &source) :
    Inherited(source)
{
}

/*--------------------------- set color terms ------------------------------*/

void LightBase::setAmbient(Real32 rRed, 
                                Real32 rGreen, 
                                Real32 rBlue, 
                                Real32 rAlpha)
{
    _ambient.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void LightBase::setDiffuse(Real32 rRed, 
                                Real32 rGreen, 
                                Real32 rBlue, 
                                Real32 rAlpha)
{
    _diffuse.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void LightBase::setSpecular(Real32 rRed, 
                                 Real32 rGreen, 
                                 Real32 rBlue, 
                                 Real32 rAlpha)
{
    _specular.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}


/** \brief Destructor
 */

LightBase::~LightBase(void)
{
}


/** \brief react to field changes
 */

void LightBase::changed(BitVector, ChangeMode)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void LightBase::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
    
Action::ResultE LightBase::draw(Action * action )
{
    glLightfv( GL_LIGHT0, GL_DIFFUSE,   
                                    _diffuse.getValue().getValueRef() );
    glLightfv( GL_LIGHT0, GL_AMBIENT,   
                                    _ambient.getValue().getValueRef() );
    glLightfv( GL_LIGHT0, GL_SPECULAR,   
                                    _specular.getValue().getValueRef() );


    // add the matrix to get into the beacon's coordinate system onto the stack

    Matrix fromworld,tobeacon;

    action->getActNode()->getToWorld( fromworld );
    fromworld.invert();

    NodePtr beacon = getBeacon();

    if ( beacon == NullNode )
    {
        SINFO << "draw: no beacon set!" << endl;

        glPushMatrix();
    }
    else
    {
        getBeacon()->getToWorld( tobeacon );
    
        tobeacon.mult( fromworld );
    
        glPushMatrix();
        glMultMatrixf( tobeacon.getValues() );
    }
    
    return Action::Continue;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

