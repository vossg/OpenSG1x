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
#include "OSGDirectionalLight.h"

OSG_USING_NAMESPACE

/*! \class osg::OSGDirectionalLight
 *  OSGDirectionalLight is an infinitely distant lightsource. Its only
 *  attribute is the light's direction.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(OSGDirectionalLight, OSGDirectionField)

OSG_FC_LAST_FIELD_IDM_DEF (OSGDirectionalLight, OSGDirectionField)

char OSGDirectionalLight::cvsid[] = "@(#)$Id: $";

OSGFieldDescription OSGDirectionalLight::_desc[] = 
{
    OSGFieldDescription(
        OSGSFVec3f::getClassType(),
        "direction", 
        OSG_FC_FIELD_IDM_DESC(OSGDirectionField),
        false,
        (OSGFieldAccessMethod) &OSGDirectionalLight::getSFDirection)
};

OSGFieldContainerType OSGDirectionalLight::_type(
    "OSGDirectionalLight",
    "OSGLightBase",
    NULL,
    (OSGPrototypeCreateF) &OSGDirectionalLight::createEmpty,
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

void OSGDirectionalLight::initMethod (void)
{
    OSGDrawAction::registerEnterDefault( getStaticType(), 
        osgMethodFunctor2BaseCPtr<OSG::OSGAction::ResultE,
                                OSGCNodePtr,  
                                OSGDirectionalLightPtr, 
                                OSGAction *>(&OSGDirectionalLight::draw));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(OSGDirectionalLight, OSGDirectionalLightPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGDirectionalLight::OSGDirectionalLight(void) :
    Inherited(),
    _direction()
{
}

/** \brief Copy Constructor
 */

OSGDirectionalLight::OSGDirectionalLight(const OSGDirectionalLight & source) :
    Inherited(),
    _direction(source._direction)
{
}

/** \brief Destructor
 */

OSGDirectionalLight::~OSGDirectionalLight(void)
{
}

/*------------------------------- set ---------------------------------------*/

void OSGDirectionalLight::setDirection(OSGReal32 rX, 
                                       OSGReal32 rY, 
                                       OSGReal32 rZ)
{
    _direction.getValue().setValues(rX, rY, rZ);
}

void OSGDirectionalLight::setDirection(const OSGVec3f &gDirection)
{
    _direction.setValue(gDirection);
}

/*------------------------------- get ---------------------------------------*/

OSGSFVec3f *OSGDirectionalLight::getSFDirection(void)
{
    return &_direction;
}

OSGVec3f &OSGDirectionalLight::getDirection(void)
{
    return _direction.getValue();
}

const OSGVec3f &OSGDirectionalLight::getDirection(void) const
{
    return _direction.getValue();
}

/*------------------------------- dump ----------------------------------*/

void OSGDirectionalLight::dump(void) const
{
    SDEBUG << "Dump OSGDirectionalLight NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
    
OSGAction::ResultE OSGDirectionalLight::draw(OSGAction * action )
{
    OSGLightBase::draw( action );

    OSGVec4f dir( _direction.getValue() );

    dir[3] = 0;
    glLightfv( GL_LIGHT0, GL_POSITION, dir.getValueRef() );
    glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 180 );

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

