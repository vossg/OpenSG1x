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
#include "OSGLightBase.h"

OSG_USING_NAMESPACE


/*! \class osg::LightBase
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

OSG_FC_FIRST_FIELD_IDM_DEF(LightBase, AmbientField)

OSG_FC_FIELD_IDM_DEF      (LightBase, DiffuseField,  AmbientField)
OSG_FC_FIELD_IDM_DEF      (LightBase, SpecularField, DiffuseField)
OSG_FC_FIELD_IDM_DEF      (LightBase, BeaconField,   SpecularField)

OSG_FC_LAST_FIELD_IDM_DEF (LightBase, BeaconField)

char LightBase::cvsid[] = "@(#)$Id: $";

FieldDescription LightBase::_desc[] = 
{
    FieldDescription(
        SFColor4f::getClassType(),
        "ambient", 
        OSG_FC_FIELD_IDM_DESC(AmbientField),
        false,
        (FieldAccessMethod) &LightBase::getSFAmbientColor), 

    FieldDescription(
        SFColor4f::getClassType(),
        "diffuse", 
        OSG_FC_FIELD_IDM_DESC(DiffuseField),
        false,
        (FieldAccessMethod) &LightBase::getSFDiffuseColor), 

    FieldDescription(
        SFColor4f::getClassType(),
        "specular", 
        OSG_FC_FIELD_IDM_DESC(SpecularField),
        false,
        (FieldAccessMethod) &LightBase::getSFSpecularColor),

    FieldDescription(
        SFNodePtr::getClassType(),
        "beacon", 
        OSG_FC_FIELD_IDM_DESC(BeaconField),
        false,
        (FieldAccessMethod) &LightBase::getSFBeacon)
};

FieldContainerType LightBase::_type("LightBase",
                                    "NodeCore",
                                    NULL,
                                    NULL,
                                    NULL, //initMethod,
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

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

OSG_ABSTR_FIELD_CONTAINER_DEF(LightBase, LightPtr)

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

LightBase::LightBase(void) :
    Inherited(),
    _ambientTerm(),
    _diffuseTerm(),
    _specularTerm(),
    _beacon()
{
}


/** \brief Destructor
 */

LightBase::~LightBase(void)
{
}

/*--------------------------- set color terms ------------------------------*/

void LightBase::setAmbientColor(Real32 rRed, 
                                Real32 rGreen, 
                                Real32 rBlue, 
                                Real32 rAlpha)
{
    _ambientTerm.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void LightBase::setAmbientColor(const Color4f &color)
{
    _ambientTerm.setValue(color);
}

void LightBase::setDiffuseColor(Real32 rRed, 
                                Real32 rGreen, 
                                Real32 rBlue, 
                                Real32 rAlpha)
{
    _diffuseTerm.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void LightBase::setDiffuseColor(const Color4f &color)
{
    _diffuseTerm.setValue(color);
}

void LightBase::setSpecularColor(Real32 rRed, 
                                 Real32 rGreen, 
                                 Real32 rBlue, 
                                 Real32 rAlpha)
{
    _specularTerm.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void LightBase::setSpecularColor(const Color4f &color)
{
    _specularTerm.setValue(color);
}

void LightBase::setBeacon(const NodePtr & beacon)
{
    _beacon.setValue(beacon);
}

/*------------------------- get color terms fields --------------------------*/

SFColor4f *LightBase::getSFAmbientColor (void)
{
    return &_ambientTerm;
}

SFColor4f *LightBase::getSFDiffuseColor (void)
{
    return &_diffuseTerm;
}

SFColor4f *LightBase::getSFSpecularColor(void)
{
    return &_specularTerm;
}

SFNodePtr *LightBase::getSFBeacon(void)
{
    return &_beacon;
}

/*------------------------- get color terms ---------------------------------*/

Color4f &LightBase::getAmbientColor(void)
{
    return _ambientTerm.getValue();
}

const Color4f &LightBase::getAmbientColor(void) const
{
    return _ambientTerm.getValue();
}

Color4f &LightBase::getDiffuseColor(void)
{
    return _diffuseTerm.getValue();
}

const Color4f &LightBase::getDiffuseColor(void) const
{
    return _diffuseTerm.getValue();
}

Color4f &LightBase::getSpecularColor(void)
{
    return _specularTerm.getValue();
}

const Color4f &LightBase::getSpecularColor(void) const
{
    return _specularTerm.getValue();
}

NodePtr &LightBase::getBeacon(void)
{
    return _beacon.getValue();
}

const NodePtr &LightBase::getBeacon(void) const
{
    return _beacon.getValue();
}

/*------------------------------- dump ----------------------------------*/

void LightBase::dump(void) const
{
    SDEBUG << "Dump LightBase NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
    
Action::ResultE LightBase::draw(Action * action )
{
    glLightfv( GL_LIGHT0, GL_DIFFUSE,   
                                    _diffuseTerm.getValue().getValueRef() );
    glLightfv( GL_LIGHT0, GL_AMBIENT,   
                                    _ambientTerm.getValue().getValueRef() );
    glLightfv( GL_LIGHT0, GL_SPECULAR,   
                                    _specularTerm.getValue().getValueRef() );


    // add the matrix to get into the beacpon's coordinate system onto the stack

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

