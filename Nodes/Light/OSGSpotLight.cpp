/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *         contact: dirk@opensg.org, vossg@igd.fhg.de, jbehr@zgdv.de         *
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

#include <OSGFieldContainerPtr.h>
#include <OSGFieldContainerType.h>
#include <OSGDrawAction.h>
#include "OSGSpotLight.h"

OSG_USING_NAMESPACE

/*! \class osg::OSGSpotLight
 * OSGSpotLight is a located lightsource. The position of the light source
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

OSG_FC_FIRST_FIELD_IDM_DEF(OSGSpotLight, OSGDirectionField)

OSG_FC_FIELD_IDM_DEF      (OSGSpotLight, 
                          OSGSpotExpField, 
                          OSGDirectionField)

OSG_FC_FIELD_IDM_DEF      (OSGSpotLight, 
                          OSGSpotCutOffField,   
                          OSGSpotExpField)

OSG_FC_LAST_FIELD_IDM_DEF (OSGSpotLight, OSGSpotCutOffField)

char OSGSpotLight::cvsid[] = "@(#)$Id: $";

OSGFieldDescription OSGSpotLight::_desc[] = 
{
    OSGFieldDescription(
        OSGSFVec3f::getClassType(),
        "direction", 
        OSG_FC_FIELD_IDM_DESC(OSGDirectionField),
        false,
        (OSGFieldAccessMethod) &OSGSpotLight::getSFDirection), 

    OSGFieldDescription(
        OSGSFReal32::getClassType(),
        "spotExponent", 
        OSG_FC_FIELD_IDM_DESC(OSGSpotExpField),
        false,
        (OSGFieldAccessMethod) &OSGSpotLight::getSFSpotExponent), 

    OSGFieldDescription(
        OSGSFReal32::getClassType(),
        "spotCutOff", 
        OSG_FC_FIELD_IDM_DESC(OSGSpotCutOffField),
        false,
        (OSGFieldAccessMethod) &OSGSpotLight::getSFSpotCutOff)
};

OSGFieldContainerType OSGSpotLight::_type(
    "OSGSpotLight",
    "OSGPointLight",
    NULL,
    (OSGPrototypeCreateF) &OSGSpotLight::createEmpty,
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

void OSGSpotLight::initMethod (void)
{
    OSGDrawAction::registerEnterDefault( getStaticType(), 
        osgMethodFunctor2BaseCPtr<OSG::OSGAction::ResultE,
                                OSGCNodePtr,  
                                OSGSpotLightPtr, 
                                OSGAction *>(&OSGSpotLight::draw));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(OSGSpotLight, OSGSpotLightPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGSpotLight::OSGSpotLight(void) :
    Inherited(),
    _direction(),
    _spotExponent(),
    _spotCutOff()
{
}

/** \brief Copy Constructor
 */

OSGSpotLight::OSGSpotLight( const OSGSpotLight & source ) :
    Inherited(),
    _direction( source._direction ),
    _spotExponent( source._spotExponent ),
    _spotCutOff( source._spotCutOff )
{
}

/** \brief Destructor
 */

OSGSpotLight::~OSGSpotLight(void)
{
}

/*------------------------------- set -----------------------------------*/

void OSGSpotLight::setSpotDirection(OSGReal32 rX, OSGReal32 rY, OSGReal32 rZ)
{
    _direction.getValue().setValues(rX, rY, rZ);
}

void OSGSpotLight::setSpotDirection(const OSGVec3f &gDirection)
{
    _direction.setValue(gDirection);
}

void OSGSpotLight::setSpotExponent(OSGReal32 rSpotExponent)
{
    _spotExponent.setValue(rSpotExponent);
}

void OSGSpotLight::setSpotCutOff(OSGReal32 rSpotCutOff)
{
    _spotCutOff.setValue(rSpotCutOff);
}

/*------------------------------- get -----------------------------------*/

OSGSFVec3f  *OSGSpotLight::getSFDirection(void)
{
    return &_direction;
}

OSGSFReal32 *OSGSpotLight::getSFSpotExponent(void)
{
    return &_spotExponent;
}

OSGSFReal32 *OSGSpotLight::getSFSpotCutOff  (void)
{
    return &_spotCutOff;
}

OSGVec3f &OSGSpotLight::getDirection  (void)
{
    return _direction.getValue();
}

const OSGVec3f &OSGSpotLight::getDirection  (void) const
{
    return _direction.getValue();
}

OSGReal32 &OSGSpotLight::getSpotExponent    (void)
{
    return _spotExponent.getValue();
}

OSGReal32  OSGSpotLight::getSpotExponent    (void) const
{
    return _spotExponent.getValue();
}

OSGReal32 &OSGSpotLight::getSpotCutOff      (void)
{
    return _spotCutOff.getValue();
}

OSGReal32  OSGSpotLight::getSpotCutOff      (void) const
{
    return _spotCutOff.getValue();
}

/*------------------------------- dump ----------------------------------*/

void OSGSpotLight::dump(void) const
{
    SDEBUG << "Dump OSGSpotLight NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
    
OSGAction::ResultE OSGSpotLight::draw(OSGAction * action )
{
    OSGPointLight::draw( action );

    OSGVec4f dir( _direction.getValue() );

    dir[3] = 0;

    glLightfv( GL_LIGHT0, GL_SPOT_DIRECTION, dir.getValueRef() );
    glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, _spotCutOff.getValue() );
    glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, _spotExponent.getValue() );

    glPopMatrix();

    return OSGAction::Continue;
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

