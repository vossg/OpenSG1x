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

#include <OSGFieldContainerPtr.h>
#include <OSGFieldContainerType.h>
#include <OSGDrawAction.h>
#include "OSGDirectionalLight.h"

OSG_USING_NAMESPACE

/*! \class osg::DirectionalLight
 *  DirectionalLight is an infinitely distant lightsource. Its only
 *  attribute is the light's direction.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(DirectionalLight, DirectionField)

OSG_FC_LAST_FIELD_IDM_DEF (DirectionalLight, DirectionField)

char DirectionalLight::cvsid[] = "@(#)$Id: $";

FieldDescription DirectionalLight::_desc[] = 
{
    FieldDescription(
        SFVec3f::getClassType(),
        "direction", 
        OSG_FC_FIELD_IDM_DESC(DirectionField),
        false,
        (FieldAccessMethod) &DirectionalLight::getSFDirection)
};

FieldContainerType DirectionalLight::_type(
    "DirectionalLight",
    "LightBase",
    NULL,
    (PrototypeCreateF) &DirectionalLight::createEmpty,
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

void DirectionalLight::initMethod (void)
{
    DrawAction::registerEnterDefault( getStaticType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                DirectionalLightPtr, 
                                Action *>(&DirectionalLight::draw));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(DirectionalLight, DirectionalLightPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

DirectionalLight::DirectionalLight(void) :
    Inherited(),
    _direction()
{
}

/** \brief Copy Constructor
 */

DirectionalLight::DirectionalLight(const DirectionalLight & source) :
    Inherited(),
    _direction(source._direction)
{
}

/** \brief Destructor
 */

DirectionalLight::~DirectionalLight(void)
{
}

/*------------------------------- set ---------------------------------------*/

void DirectionalLight::setDirection(Real32 rX, 
                                    Real32 rY, 
                                    Real32 rZ)
{
    _direction.getValue().setValues(rX, rY, rZ);
}

void DirectionalLight::setDirection(const Vec3f &gDirection)
{
    _direction.setValue(gDirection);
}

/*------------------------------- get ---------------------------------------*/

SFVec3f *DirectionalLight::getSFDirection(void)
{
    return &_direction;
}

Vec3f &DirectionalLight::getDirection(void)
{
    return _direction.getValue();
}

const Vec3f &DirectionalLight::getDirection(void) const
{
    return _direction.getValue();
}

/*------------------------------- dump ----------------------------------*/

void DirectionalLight::dump(void) const
{
    SDEBUG << "Dump DirectionalLight NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
    
Action::ResultE DirectionalLight::draw(Action * action )
{
    LightBase::draw( action );

    Vec4f dir( _direction.getValue() );

    dir[3] = 0;
    glLightfv( GL_LIGHT0, GL_POSITION, dir.getValueRef() );
    glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 180 );

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

