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

#include <OSGFieldContainerPtr.h>
#include <OSGFieldContainerType.h>
#include <OSGDrawAction.h>
#include "OSGSpotLight.h"

OSG_USING_NAMESPACE

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

OSG_FC_FIRST_FIELD_IDM_DEF(SpotLight, DirectionField)

OSG_FC_FIELD_IDM_DEF      (SpotLight, 
                           SpotExpField, 
                           DirectionField)

OSG_FC_FIELD_IDM_DEF      (SpotLight, 
                           SpotCutOffField,   
                           SpotExpField)

OSG_FC_LAST_FIELD_IDM_DEF (SpotLight, SpotCutOffField)

char SpotLight::cvsid[] = "@(#)$Id: $";

FieldDescription SpotLight::_desc[] = 
{
    FieldDescription(
        SFVec3f::getClassType(),
        "direction", 
        OSG_FC_FIELD_IDM_DESC(DirectionField),
        false,
        (FieldAccessMethod) &SpotLight::getSFDirection), 

    FieldDescription(
        SFReal32::getClassType(),
        "spotExponent", 
        OSG_FC_FIELD_IDM_DESC(SpotExpField),
        false,
        (FieldAccessMethod) &SpotLight::getSFSpotExponent), 

    FieldDescription(
        SFReal32::getClassType(),
        "spotCutOff", 
        OSG_FC_FIELD_IDM_DESC(SpotCutOffField),
        false,
        (FieldAccessMethod) &SpotLight::getSFSpotCutOff)
};

FieldContainerType SpotLight::_type(
    "SpotLight",
    "PointLight",
    NULL,
    (PrototypeCreateF) &SpotLight::createEmpty,
    initMethod,
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

void SpotLight::initMethod (void)
{
    DrawAction::registerEnterDefault( getStaticType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                SpotLightPtr, 
                                Action *>(&SpotLight::draw));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(SpotLight, SpotLightPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

SpotLight::SpotLight(void) :
    Inherited(),
    _direction(),
    _spotExponent(),
    _spotCutOff()
{
}

/** \brief Copy Constructor
 */

SpotLight::SpotLight( const SpotLight & source ) :
    Inherited(),
    _direction( source._direction ),
    _spotExponent( source._spotExponent ),
    _spotCutOff( source._spotCutOff )
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
    _direction.getValue().setValues(rX, rY, rZ);
}

void SpotLight::setSpotDirection(const Vec3f &gDirection)
{
    _direction.setValue(gDirection);
}

void SpotLight::setSpotExponent(Real32 rSpotExponent)
{
    _spotExponent.setValue(rSpotExponent);
}

void SpotLight::setSpotCutOff(Real32 rSpotCutOff)
{
    _spotCutOff.setValue(rSpotCutOff);
}

/*------------------------------- get -----------------------------------*/

SFVec3f  *SpotLight::getSFDirection(void)
{
    return &_direction;
}

SFReal32 *SpotLight::getSFSpotExponent(void)
{
    return &_spotExponent;
}

SFReal32 *SpotLight::getSFSpotCutOff  (void)
{
    return &_spotCutOff;
}

Vec3f &SpotLight::getDirection  (void)
{
    return _direction.getValue();
}

const Vec3f &SpotLight::getDirection  (void) const
{
    return _direction.getValue();
}

Real32 &SpotLight::getSpotExponent    (void)
{
    return _spotExponent.getValue();
}

Real32  SpotLight::getSpotExponent    (void) const
{
    return _spotExponent.getValue();
}

Real32 &SpotLight::getSpotCutOff      (void)
{
    return _spotCutOff.getValue();
}

Real32  SpotLight::getSpotCutOff      (void) const
{
    return _spotCutOff.getValue();
}

/*------------------------------- dump ----------------------------------*/

void SpotLight::dump(void) const
{
    SDEBUG << "Dump SpotLight NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
    
Action::ResultE SpotLight::draw(Action * action )
{
    PointLight::draw( action );

    Vec4f dir( _direction.getValue() );

    dir[3] = 0;

    glLightfv( GL_LIGHT0, GL_SPOT_DIRECTION, dir.getValueRef() );
    glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, _spotCutOff.getValue() );
    glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, _spotExponent.getValue() );

    glPopMatrix();

    return Action::Continue;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

