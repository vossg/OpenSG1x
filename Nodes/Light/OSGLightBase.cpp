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
#include "OSGLightBase.h"

OSG_USING_NAMESPACE


/*! \class osg::OSGLightBase
 *  OSGLightBase is the base class for all the light source nodes.
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

OSG_FC_FIRST_FIELD_IDM_DEF(OSGLightBase, OSGAmbientField)

OSG_FC_FIELD_IDM_DEF      (OSGLightBase, OSGDiffuseField,  OSGAmbientField)
OSG_FC_FIELD_IDM_DEF      (OSGLightBase, OSGSpecularField, OSGDiffuseField)
OSG_FC_FIELD_IDM_DEF      (OSGLightBase, OSGBeaconField,   OSGSpecularField)

OSG_FC_LAST_FIELD_IDM_DEF (OSGLightBase, OSGBeaconField)

char OSGLightBase::cvsid[] = "@(#)$Id: $";

OSGFieldDescription OSGLightBase::_desc[] = 
{
    OSGFieldDescription(
        OSGSFColor4f::getClassType(),
        "ambient", 
        OSG_FC_FIELD_IDM_DESC(OSGAmbientField),
        false,
        (OSGFieldAccessMethod) &OSGLightBase::getSFAmbientColor), 

    OSGFieldDescription(
        OSGSFColor4f::getClassType(),
        "diffuse", 
        OSG_FC_FIELD_IDM_DESC(OSGDiffuseField),
        false,
        (OSGFieldAccessMethod) &OSGLightBase::getSFDiffuseColor), 

    OSGFieldDescription(
        OSGSFColor4f::getClassType(),
        "specular", 
        OSG_FC_FIELD_IDM_DESC(OSGSpecularField),
        false,
        (OSGFieldAccessMethod) &OSGLightBase::getSFSpecularColor),

    OSGFieldDescription(
        OSGSFNodePtr::getClassType(),
        "beacon", 
        OSG_FC_FIELD_IDM_DESC(OSGBeaconField),
        false,
        (OSGFieldAccessMethod) &OSGLightBase::getSFBeacon)
};

OSGFieldContainerType OSGLightBase::_type("OSGLightBase",
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

OSG_ABSTR_FIELD_CONTAINER_DEF(OSGLightBase, OSGLightPtr)

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGLightBase::OSGLightBase(void) :
    Inherited(),
    _ambientTerm(),
    _diffuseTerm(),
    _specularTerm(),
    _beacon()
{
}


/** \brief Destructor
 */

OSGLightBase::~OSGLightBase(void)
{
}

/*--------------------------- set color terms ------------------------------*/

void OSGLightBase::setAmbientColor(OSGReal32 rRed, 
                                   OSGReal32 rGreen, 
                                   OSGReal32 rBlue, 
                                   OSGReal32 rAlpha)
{
    _ambientTerm.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void OSGLightBase::setAmbientColor(const OSGColor4f &color)
{
    _ambientTerm.setValue(color);
}

void OSGLightBase::setDiffuseColor(OSGReal32 rRed, 
                                   OSGReal32 rGreen, 
                                   OSGReal32 rBlue, 
                                   OSGReal32 rAlpha)
{
    _diffuseTerm.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void OSGLightBase::setDiffuseColor(const OSGColor4f &color)
{
    _diffuseTerm.setValue(color);
}

void OSGLightBase::setSpecularColor(OSGReal32 rRed, 
                                    OSGReal32 rGreen, 
                                    OSGReal32 rBlue, 
                                    OSGReal32 rAlpha)
{
    _specularTerm.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void OSGLightBase::setSpecularColor(const OSGColor4f &color)
{
    _specularTerm.setValue(color);
}

void OSGLightBase::setBeacon(const OSGNodePtr & beacon)
{
    _beacon.setValue(beacon);
}

/*------------------------- get color terms fields --------------------------*/

OSGSFColor4f *OSGLightBase::getSFAmbientColor (void)
{
    return &_ambientTerm;
}

OSGSFColor4f *OSGLightBase::getSFDiffuseColor (void)
{
    return &_diffuseTerm;
}

OSGSFColor4f *OSGLightBase::getSFSpecularColor(void)
{
    return &_specularTerm;
}

OSGSFNodePtr *OSGLightBase::getSFBeacon(void)
{
    return &_beacon;
}

/*------------------------- get color terms ---------------------------------*/

OSGColor4f &OSGLightBase::getAmbientColor(void)
{
    return _ambientTerm.getValue();
}

const OSGColor4f &OSGLightBase::getAmbientColor(void) const
{
    return _ambientTerm.getValue();
}

OSGColor4f &OSGLightBase::getDiffuseColor(void)
{
    return _diffuseTerm.getValue();
}

const OSGColor4f &OSGLightBase::getDiffuseColor(void) const
{
    return _diffuseTerm.getValue();
}

OSGColor4f &OSGLightBase::getSpecularColor(void)
{
    return _specularTerm.getValue();
}

const OSGColor4f &OSGLightBase::getSpecularColor(void) const
{
    return _specularTerm.getValue();
}

OSGNodePtr &OSGLightBase::getBeacon(void)
{
    return _beacon.getValue();
}

const OSGNodePtr &OSGLightBase::getBeacon(void) const
{
    return _beacon.getValue();
}

/*------------------------------- dump ----------------------------------*/

void OSGLightBase::dump(void) const
{
    SDEBUG << "Dump OSGLightBase NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
    
OSGAction::ResultE OSGLightBase::draw(OSGAction * action )
{
    glLightfv( GL_LIGHT0, GL_DIFFUSE,   
                                    _diffuseTerm.getValue().getValueRef() );
    glLightfv( GL_LIGHT0, GL_AMBIENT,   
                                    _ambientTerm.getValue().getValueRef() );
    glLightfv( GL_LIGHT0, GL_SPECULAR,   
                                    _specularTerm.getValue().getValueRef() );


    // add the matrix to get into the beacpon's coordinate system onto the stack

    OSGMatrix fromworld,tobeacon;

    action->getActNode()->getToWorld( fromworld );
    fromworld.invert();

    OSGNodePtr beacon = getBeacon();

    if ( beacon == OSGNullNode )
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

