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

#include "OSGSpotLight.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SpotLight
 * SpotLight is a located lightsource. The position of the light source
 * (in the beacon's coordinate system) is defined by the \c position 
 * attribute, its direction by the \c direction attribute. The spot has an 
 * exponential fallof, controlled by the \c spotExponent attribute and a 
 * maximum opening angle, defined by the \c spotCutOff attribute.
 * The influence of the light diminishes with distance, controlled
 * by the \c constantAttenuation, \c linearAttenuation and \c
 * quadraticAttenuation attributes. 
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char SpotLight::cvsid[] = "@(#)$Id: $";

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
OSG::Action::ResultE SpotLight::SLightDrawEnter(CNodePtr &cnode, 
                                                Action  *pAction)
{
    NodeCore  *pNC = cnode.getCPtr();
    SpotLight *pSC = dynamic_cast<SpotLight *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "PLDE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->drawEnter(pAction);
    }
}
OSG::Action::ResultE SpotLight::SLightDrawLeave(CNodePtr &cnode, 
                                                Action  *pAction)
{
    NodeCore  *pNC = cnode.getCPtr();
    SpotLight *pSC = dynamic_cast<SpotLight *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "PLDL: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->drawLeave(pAction);
    }
}
#endif

void SpotLight::initMethod (void)
{
#ifndef OSG_NOFUNCTORS
    DrawAction::registerEnterDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                SpotLightPtr, 
                                Action *>(&SpotLight::drawEnter));

    DrawAction::registerLeaveDefault( getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                SpotLightPtr, 
                                Action *>(&SpotLight::drawLeave));

#else

    DrawAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                         SpotLight::SLightDrawEnter));

    DrawAction::registerLeaveDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                         SpotLight::SLightDrawLeave));

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

SpotLight::SpotLight(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

SpotLight::SpotLight(const SpotLight &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

SpotLight::~SpotLight(void)
{
}

/*------------------------------- set -----------------------------------*/

void SpotLight::setSpotDirection(Real32 rX, Real32 rY, Real32 rZ)
{
    _sfDirection.getValue().setValues(rX, rY, rZ);
}


/** \brief react to field changes
 */

void SpotLight::changed(BitVector, ChangeMode)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void SpotLight::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
       
Action::ResultE SpotLight::drawEnter(Action * action )
{   
    if ( ! getOn() )
    	return Action::Continue;

    DrawAction *da = (DrawAction *)action;
    GLenum light = GL_LIGHT0 + da->getLightCount();
	
    PointLight::drawEnter( action );

    Vec4f dir( _sfDirection.getValue() );

    dir[3] = 0;

    glLightfv( light, GL_SPOT_DIRECTION, dir.getValues() );
    glLightf( light, GL_SPOT_CUTOFF, _sfSpotCutOff.getValue() );
    glLightf( light, GL_SPOT_EXPONENT, _sfSpotExponent.getValue() );

    glPopMatrix();

    return Action::Continue;
}
    
Action::ResultE SpotLight::drawLeave(Action * action )
{
    if ( ! getOn() )
    	return Action::Continue;

    return LightBase::drawLeave( action );
}


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

