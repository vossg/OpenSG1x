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

#define OSG_COMPILEMISC
#define OSG_COMPILEVRMLTRANSFORMINST

#include "OSGVRMLTransform.h"
#include "OSGDrawAction.h"

OSG_USING_NAMESPACE

/** \fn const char *VRMLTransform::getClassname(void)
 *  \brief Classname
 */

/** \typedef VRMLTransform::Inherited
 *  \brief Parent type
 */

/** \fn VRMLTransform::VRMLTransform(const VRMLTransform &source)
 *  \brief Not implemented.
 */

/** \fn void VRMLTransform::operator =(const VRMLTransform &source)
 *  \brief Not implemented.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

#pragma instantiate SField<VRMLTransformPtr>::_fieldType
#pragma instantiate MField<VRMLTransformPtr>::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, VRMLTransformPtr, OSG_MISC_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, VRMLTransformPtr, OSG_MISC_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(VRMLTransform, CenterField)

OSG_FC_FIELD_IDM_DEF      (VRMLTransform,
						   RotationField, 
                           CenterField)
OSG_FC_FIELD_IDM_DEF      (VRMLTransform,
						   ScaleField, 
                           RotationField)
OSG_FC_FIELD_IDM_DEF      (VRMLTransform,
						   ScaleOrientationField, 
                           ScaleField)
OSG_FC_FIELD_IDM_DEF      (VRMLTransform,
						   TranslationField, 
                           ScaleOrientationField)

OSG_FC_LAST_FIELD_IDM_DEF (VRMLTransform, VRMLTransform)

char VRMLTransform::cvsid[] = "@(#)$Id: $";

/** \brief Group field description
 */

FieldDescription VRMLTransform::_desc[] = 
{
    FieldDescription(SFVec3f::getClassType(), 
                     "center", 
                     OSG_FC_FIELD_IDM_DESC(CenterField),
                     false,
                     (FieldAccessMethod) &VRMLTransform::getSFCenter),
    FieldDescription(SFQuaternion::getClassType(), 
                     "rotation", 
                     OSG_FC_FIELD_IDM_DESC(RotationField),
                     false,
                     (FieldAccessMethod) &VRMLTransform::getSFRotation),
    FieldDescription(SFVec3f::getClassType(), 
                     "scale", 
                     OSG_FC_FIELD_IDM_DESC(ScaleField),
                     false,
                     (FieldAccessMethod) &VRMLTransform::getSFScale),
    FieldDescription(SFQuaternion::getClassType(), 
                     "scaleOrientation", 
                     OSG_FC_FIELD_IDM_DESC(ScaleOrientationField),
                     false,
                    (FieldAccessMethod) &VRMLTransform::getSFScaleOrientation),
    FieldDescription(SFVec3f::getClassType(), 
                     "translation", 
                     OSG_FC_FIELD_IDM_DESC(TranslationField),
                     false,
                     (FieldAccessMethod) &VRMLTransform::getSFTranslation)
};

/** \brief VRMLTransform type
 */

FieldContainerType VRMLTransform::_type(
    "VRMLTransform",
    "Transform",
    NULL,
    (PrototypeCreateF) &VRMLTransform::createEmpty,
    initMethod,
    _desc,
    sizeof(_desc));


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

void VRMLTransform::initMethod (void)
{
    DrawAction::registerEnterDefault( getStaticType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                VRMLTransformPtr, 
                                Action *>(&VRMLTransform::drawEnter));
    DrawAction::registerLeaveDefault( getStaticType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                CNodePtr,  
                                VRMLTransformPtr, 
                                Action *>(&VRMLTransform::drawLeave));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(VRMLTransform, VRMLTransformPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLTransform::VRMLTransform(void) :
    Inherited(),
    _center          (),
    _rotation        (),
    _scale           (Vec3f(1., 1., 1.)),
    _scaleOrientation(),
    _translation     ()
{
}

/** \brief Copy Constructor
 */

VRMLTransform::VRMLTransform(const VRMLTransform &source) :
    Inherited        (source                  ),
    _center          (source._center          ),
    _rotation        (source._rotation        ),
    _scale           (source._scale           ),
    _scaleOrientation(source._scaleOrientation),
    _translation     (source._translation     )
{
}

/** \brief Destructor
 */

VRMLTransform::~VRMLTransform(void)
{
}

/*------------------------------ access -----------------------------------*/

SFVec3f *VRMLTransform::getSFCenter(void)
{
    return &_center;
}

SFQuaternion *VRMLTransform::getSFRotation(void)
{
    return &_rotation;;
}

SFVec3f *VRMLTransform::getSFScale(void)
{
    return &_scale;
}

SFQuaternion *VRMLTransform::getSFScaleOrientation(void)
{
    return &_scaleOrientation;
}

SFVec3f *VRMLTransform::getSFTranslation(void)
{
    return &_translation;
}

Vec3f &VRMLTransform::getCenter(void)
{
    return _center.getValue();
}

const Vec3f &VRMLTransform::getCenter(void) const
{
    return _center.getValue();
}

Quaternion &VRMLTransform::getRotation(void)
{
    return _rotation.getValue();
}

const Quaternion &VRMLTransform::getRotation(void) const
{
    return _rotation.getValue();
}

Vec3f &VRMLTransform::getScale(void)
{
    return _scale.getValue();
}

const Vec3f &VRMLTransform::getScale(void) const
{
    return _scale.getValue();
}

Quaternion &VRMLTransform::getScaleOrientation(void)
{
    return _scaleOrientation.getValue();
}

const Quaternion &VRMLTransform::getScaleOrientation(void) const
{
    return _scaleOrientation.getValue();
}

Vec3f &VRMLTransform::getTranslation(void)
{
    return _translation.getValue();
}

const Vec3f &VRMLTransform::getTranslation(void) const
{
    return _translation.getValue();
}

void VRMLTransform::changed(BitVector, 
                            ChangeMode)
{
    getMatrix().setTransform(getTranslation     (),
                             getRotation        (),
                             getScale           (),
                             getScaleOrientation(),
                             getCenter          ());
}

/*------------------------------- dump ----------------------------------*/

void VRMLTransform::dump(void) const
{
    SDEBUG << "Dump VRMLTransform NI" << endl;
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

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

