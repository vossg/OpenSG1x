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

#include <OSGFieldContainerPtr.h>
#include <OSGFieldContainerType.h>
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
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(PointLight, PositionField)

OSG_FC_FIELD_IDM_DEF      (PointLight, 
                           ConstAttenField, 
                           PositionField)

OSG_FC_FIELD_IDM_DEF      (PointLight, 
                           LinAttenField,   
                           ConstAttenField)

OSG_FC_FIELD_IDM_DEF      (PointLight, 
                           QuadAttenField, 
                           LinAttenField)

OSG_FC_LAST_FIELD_IDM_DEF (PointLight, QuadAttenField)

char PointLight::cvsid[] = "@(#)$Id: $";

FieldDescription PointLight::_desc[] = 
{
	FieldDescription(
        SFPnt3f::getClassType(),
        "position", 
        OSG_FC_FIELD_IDM_DESC(PositionField),
        false,
        (FieldAccessMethod) &PointLight::getSFPosition), 

	FieldDescription(
        SFReal32::getClassType(),
        "constantAttenuation", 
        OSG_FC_FIELD_IDM_DESC(ConstAttenField),
        false,
        (FieldAccessMethod) &PointLight::getSFConstantAttenuation), 

	FieldDescription(
        SFReal32::getClassType(),
        "linearAttenuation", 
        OSG_FC_FIELD_IDM_DESC(LinAttenField),
        false,
        (FieldAccessMethod) &PointLight::getSFLinearAttenuation), 

	FieldDescription(
        SFReal32::getClassType(),
        "quadraticAttenuation", 
        OSG_FC_FIELD_IDM_DESC(QuadAttenField),
        false,
        (FieldAccessMethod) &PointLight::getSFQuadraticAttenuation)
};

FieldContainerType PointLight::_type(
    "PointLight",
    "LightBase",
    NULL,
    (PrototypeCreateF) &PointLight::createEmpty,
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

void PointLight::initMethod (void)
{
	DrawAction::registerEnterDefault( getClassType(), 
		osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
								CNodePtr,  
								PointLightPtr, 
								Action *>(&PointLight::draw));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(PointLight, PointLightPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

PointLight::PointLight(void) :
    Inherited(),
    _position(),
    _constantAttenuation(),
    _linearAttenuation(),
    _quadraticAttenuation()
{
}

/** \brief Copy Constructor
 */

PointLight::PointLight(const PointLight &source) :
    Inherited(),
    _position            (source._position            ),
    _constantAttenuation (source._constantAttenuation ),
    _linearAttenuation   (source._linearAttenuation   ),
    _quadraticAttenuation(source._quadraticAttenuation)
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
    _position.getValue().setValues(rX, rY, rZ);
}

void PointLight::setPosition(const Pnt3f &gPosition)
{
    _position.setValue(gPosition);
}

void PointLight::setAttenuation(Real32 rConstant, 
                                Real32 rLinear, 
                                Real32 rQuadratic)
{
    _constantAttenuation.setValue(rConstant);
    _linearAttenuation.setValue(rLinear);
    _quadraticAttenuation.setValue(rQuadratic);
}


/*------------------------------- get ---------------------------------------*/

SFPnt3f  *PointLight::getSFPosition(void)
{
    return &_position;
}

SFReal32 *PointLight::getSFConstantAttenuation (void)
{
    return &_constantAttenuation;
}

SFReal32 *PointLight::getSFLinearAttenuation   (void)
{
    return &_linearAttenuation;
}

SFReal32 *PointLight::getSFQuadraticAttenuation(void)
{
    return &_quadraticAttenuation;
}
    
Pnt3f &PointLight::getPosition(void)
{
    return _position.getValue();
}

const Pnt3f &PointLight::getPosition(void) const
{
    return _position.getValue();
}

Real32 &PointLight::getConstantAttenuation (void)
{
    return _constantAttenuation.getValue();
}

Real32  PointLight::getConstantAttenuation (void) const
{
    return _constantAttenuation.getValue();
}


Real32 &PointLight::getLinearAttenuation   (void)
{
    return _linearAttenuation.getValue();
}

Real32  PointLight::getLinearAttenuation   (void) const
{
    return _linearAttenuation.getValue();
}


Real32 &PointLight::getQuadraticAttenuation(void)
{
    return _quadraticAttenuation.getValue();
}

Real32  PointLight::getQuadraticAttenuation(void) const
{
    return _quadraticAttenuation.getValue();
}

/*------------------------------- dump ----------------------------------*/

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

	Vec4f pos( _position.getValue() );

	pos[3] = 1;
	glLightfv( GL_LIGHT0, GL_POSITION, pos.getValueRef() );
	glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 180 );

	glPopMatrix();

	return Action::Continue;
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

