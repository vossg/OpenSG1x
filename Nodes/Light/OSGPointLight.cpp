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

#include <OSGFieldContainerPtr.h>
#include <OSGFieldContainerType.h>
#include <OSGDrawAction.h>
#include "OSGPointLight.h"

OSG_USING_NAMESPACE

/*! \class osg::OSGPointLight
 * OSGPointLight is a located lightsource. The position of the light source
 * (in the beacon's coordinate system) is defined by the \c position 
 * attribute. The influence of the light diminishes with distance, controlled
 * by the \c constantAttenuation, \c linearAttenuation and \c
 * quadraticAttenuation attributes.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(OSGPointLight, OSGPositionField)

OSG_FC_FIELD_IDM_DEF      (OSGPointLight, 
                          OSGConstAttenField, 
                          OSGPositionField)

OSG_FC_FIELD_IDM_DEF      (OSGPointLight, 
                          OSGLinAttenField,   
                          OSGConstAttenField)

OSG_FC_FIELD_IDM_DEF      (OSGPointLight, 
                          OSGQuadAttenField, 
                          OSGLinAttenField)

OSG_FC_LAST_FIELD_IDM_DEF (OSGPointLight, OSGQuadAttenField)

char OSGPointLight::cvsid[] = "@(#)$Id: $";

OSGFieldDescription OSGPointLight::_desc[] = 
{
	OSGFieldDescription(
        OSGSFPnt3f::getClassType(),
        "position", 
        OSG_FC_FIELD_IDM_DESC(OSGPositionField),
        false,
        (OSGFieldAccessMethod) &OSGPointLight::getSFPosition), 

	OSGFieldDescription(
        OSGSFReal32::getClassType(),
        "constantAttenuation", 
        OSG_FC_FIELD_IDM_DESC(OSGConstAttenField),
        false,
        (OSGFieldAccessMethod) &OSGPointLight::getSFConstantAttenuation), 

	OSGFieldDescription(
        OSGSFReal32::getClassType(),
        "linearAttenuation", 
        OSG_FC_FIELD_IDM_DESC(OSGLinAttenField),
        false,
        (OSGFieldAccessMethod) &OSGPointLight::getSFLinearAttenuation), 

	OSGFieldDescription(
        OSGSFReal32::getClassType(),
        "quadraticAttenuation", 
        OSG_FC_FIELD_IDM_DESC(OSGQuadAttenField),
        false,
        (OSGFieldAccessMethod) &OSGPointLight::getSFQuadraticAttenuation)
};

OSGFieldContainerType OSGPointLight::_type(
    "OSGPointLight",
    "OSGLightBase",
    NULL,
    (OSGPrototypeCreateF) &OSGPointLight::createEmpty,
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

void OSGPointLight::initMethod (void)
{
	OSGDrawAction::registerEnterDefault( getStaticType(), 
		osgMethodFunctor2BaseCPtr<OSG::OSGAction::ResultE,
								OSGCNodePtr,  
								OSGPointLightPtr, 
								OSGAction *>(&OSGPointLight::draw));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(OSGPointLight, OSGPointLightPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGPointLight::OSGPointLight(void) :
    Inherited(),
    _position(),
    _constantAttenuation(),
    _linearAttenuation(),
    _quadraticAttenuation()
{
}

/** \brief Copy Constructor
 */

OSGPointLight::OSGPointLight(const OSGPointLight &source) :
    Inherited(),
    _position( source._position ),
    _constantAttenuation( source._constantAttenuation ),
    _linearAttenuation( source._linearAttenuation ),
    _quadraticAttenuation( source._quadraticAttenuation )
{
}

/** \brief Destructor
 */

OSGPointLight::~OSGPointLight(void)
{
}

/*------------------------------- set ---------------------------------------*/

void OSGPointLight::setPosition(OSGReal32 rX, OSGReal32 rY, OSGReal32 rZ)
{
    _position.getValue().setValues(rX, rY, rZ);
}

void OSGPointLight::setPosition(const OSGPnt3f &gPosition)
{
    _position.setValue(gPosition);
}

void OSGPointLight::setAttenuation(OSGReal32 rConstant, 
                                   OSGReal32 rLinear, 
                                   OSGReal32 rQuadratic)
{
    _constantAttenuation.setValue(rConstant);
    _linearAttenuation.setValue(rLinear);
    _quadraticAttenuation.setValue(rQuadratic);
}


/*------------------------------- get ---------------------------------------*/

OSGSFPnt3f  *OSGPointLight::getSFPosition(void)
{
    return &_position;
}

OSGSFReal32 *OSGPointLight::getSFConstantAttenuation (void)
{
    return &_constantAttenuation;
}

OSGSFReal32 *OSGPointLight::getSFLinearAttenuation   (void)
{
    return &_linearAttenuation;
}

OSGSFReal32 *OSGPointLight::getSFQuadraticAttenuation(void)
{
    return &_quadraticAttenuation;
}
    
OSGPnt3f &OSGPointLight::getPosition(void)
{
    return _position.getValue();
}

const OSGPnt3f &OSGPointLight::getPosition(void) const
{
    return _position.getValue();
}

OSGReal32 &OSGPointLight::getConstantAttenuation (void)
{
    return _constantAttenuation.getValue();
}

OSGReal32  OSGPointLight::getConstantAttenuation (void) const
{
    return _constantAttenuation.getValue();
}


OSGReal32 &OSGPointLight::getLinearAttenuation   (void)
{
    return _linearAttenuation.getValue();
}

OSGReal32  OSGPointLight::getLinearAttenuation   (void) const
{
    return _linearAttenuation.getValue();
}


OSGReal32 &OSGPointLight::getQuadraticAttenuation(void)
{
    return _quadraticAttenuation.getValue();
}

OSGReal32  OSGPointLight::getQuadraticAttenuation(void) const
{
    return _quadraticAttenuation.getValue();
}

/*------------------------------- dump ----------------------------------*/

void OSGPointLight::dump(void) const
{
    SDEBUG << "Dump OSGPointLight NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
	
OSGAction::ResultE OSGPointLight::draw(OSGAction * action )
{
	OSGLightBase::draw( action );

	OSGVec4f pos( _position.getValue() );

	pos[3] = 1;
	glLightfv( GL_LIGHT0, GL_POSITION, pos.getValueRef() );
	glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 180 );

	glPopMatrix();

	return OSGAction::Continue;
}

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

