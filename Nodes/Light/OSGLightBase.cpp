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

#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
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
     Inherited(),
    _pChunk   ()
{
}

/** \brief Copy Constructor
 */

LightBase::LightBase(const LightBase &source) :
     Inherited(source),
    _pChunk   (source._pChunk)
{
}

/*--------------------------- set color terms ------------------------------*/

void LightBase::setAmbient(Real32 rRed, 
                                Real32 rGreen, 
                                Real32 rBlue, 
                                Real32 rAlpha)
{
    _sfAmbient.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void LightBase::setDiffuse(Real32 rRed, 
                                Real32 rGreen, 
                                Real32 rBlue, 
                                Real32 rAlpha)
{
    _sfDiffuse.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void LightBase::setSpecular(Real32 rRed, 
                                 Real32 rGreen, 
                                 Real32 rBlue, 
                                 Real32 rAlpha)
{
    _sfSpecular.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
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


LightChunkPtr LightBase::getChunk(void)
{
    return _pChunk;
}

void LightBase::makeChunk(void)
{
    if(_pChunk == NullFC)
    {
        _pChunk = LightChunk::create();
    }

    _pChunk->setAmbient (getAmbient());
    _pChunk->setDiffuse (getDiffuse());
    _pChunk->setSpecular(getSpecular());
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
    
Action::ResultE LightBase::drawEnter(Action * action )
{
    DrawAction *da = (DrawAction *)action;
    GLenum light = GL_LIGHT0 + da->getLightCount();
    
    da->incLightCount();
    
    glEnable( light );
    
    glLightfv( light, GL_DIFFUSE,   
                                    _sfDiffuse.getValue().getValueRef() );
    glLightfv( light, GL_AMBIENT,   
                                    _sfAmbient.getValue().getValueRef() );
    glLightfv( light, GL_SPECULAR,   
                                    _sfSpecular.getValue().getValueRef() );

    glLightf ( light, GL_CONSTANT_ATTENUATION,   
                             _sfConstantAttenuation.getValue() );
    glLightf ( light, GL_LINEAR_ATTENUATION,   
                             _sfLinearAttenuation.getValue() );
    glLightf ( light, GL_QUADRATIC_ATTENUATION,   
                             _sfQuadraticAttenuation.getValue() );

    // add the matrix to get into the beacon's coordinate system onto the stack

    Matrix fromworld,tobeacon;

    action->getActNode()->getToWorld( fromworld );
    fromworld.invert();

    NodePtr beacon = getBeacon();

    if ( beacon == NullFC )
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
    
Action::ResultE LightBase::drawLeave(Action * action )
{
    DrawAction *da = (DrawAction *)action;
     
    da->decLightCount();

    GLenum light = GL_LIGHT0 + da->getLightCount();
   
    glDisable( light );
   
    return Action::Continue;
}

Action::ResultE LightBase::renderEnter(Action *action)
{
//    fprintf(stderr, "LightBase::renderEnter\n");

    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->dropLight(this);

    return Action::Continue;
}

Action::ResultE LightBase::renderLeave(Action *action)
{
//    fprintf(stderr, "LightBase::renderLeave\n");
    return Action::Continue;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

