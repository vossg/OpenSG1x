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

#include "OSGPointLight.h"

OSG_USING_NAMESPACE

/*! \class osg::PointLight
 * PointLight is a located lightsource. The position of the light source
 * (in the beacon's coordinate system) is defined by the \c position 
 * attribute. The influence of the light diminishes with distance, controlled
 * by the \c constantAttenuation, \c linearAttenuation and \c
 * quadraticAttenuation attributes.
 */

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PointLight



*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char PointLight::cvsid[] = "@(#)$Id: $";

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

#ifdef OSG_NOFUNCTORS
OSG::Action::ResultE PointLight::PLightDrawEnter(CNodePtr &cnode, 
                                                 Action  *pAction)
{
    NodeCore   *pNC = cnode.getCPtr();
    PointLight *pSC = dynamic_cast<PointLight *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "PLDE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->draw(pAction);
    }
}
#endif

void PointLight::initMethod (void)
{
#ifndef OSG_NOFUNCTORS
	DrawAction::registerEnterDefault( getClassType(), 
		osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
								CNodePtr,  
								PointLightPtr, 
								Action *>(&PointLight::draw));

#else

    DrawAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                         PointLight::PLightDrawEnter));

#endif
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

PointLight::PointLight(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

PointLight::PointLight(const PointLight &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

PointLight::~PointLight(void)
{
}

/*------------------------------- set ---------------------------------------*/

void PointLight::setPosition(Real32 rX, Real32 rY, Real32 rZ)
{
    _sfPosition.getValue().setValues(rX, rY, rZ);
}

void PointLight::setAttenuation(Real32 rConstant, 
                                Real32 rLinear, 
                                Real32 rQuadratic)
{
    _sfConstantAttenuation.setValue(rConstant);
    _sfLinearAttenuation.setValue(rLinear);
    _sfQuadraticAttenuation.setValue(rQuadratic);
}

/** \brief react to field changes
 */

void PointLight::changed(BitVector, ChangeMode)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void PointLight::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
	
Action::ResultE PointLight::draw(Action * action )
{
	LightBase::draw( action );

	Vec4f pos( _sfPosition.getValue() );

	pos[3] = 1;
	glLightfv( GL_LIGHT0, GL_POSITION, pos.getValuesRef() );
	glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 180 );

	glPopMatrix();

	return Action::Continue;
}


