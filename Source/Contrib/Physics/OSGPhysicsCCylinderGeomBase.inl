/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class PhysicsCCylinderGeom!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &PhysicsCCylinderGeomBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 PhysicsCCylinderGeomBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
PhysicsCCylinderGeomPtr PhysicsCCylinderGeomBase::create(void) 
{
    PhysicsCCylinderGeomPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = PhysicsCCylinderGeomPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
PhysicsCCylinderGeomPtr PhysicsCCylinderGeomBase::createEmpty(void) 
{ 
    PhysicsCCylinderGeomPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the PhysicsCCylinderGeom::_sfParams field.
inline
SFVec2f *PhysicsCCylinderGeomBase::getSFParams(void)
{
    return &_sfParams;
}


//! Get the value of the PhysicsCCylinderGeom::_sfParams field.
inline
Vec2f &PhysicsCCylinderGeomBase::getParams(void)
{
    return _sfParams.getValue();
}

//! Get the value of the PhysicsCCylinderGeom::_sfParams field.
inline
const Vec2f &PhysicsCCylinderGeomBase::getParams(void) const
{
    return _sfParams.getValue();
}

//! Set the value of the PhysicsCCylinderGeom::_sfParams field.
inline
void PhysicsCCylinderGeomBase::setParams(const Vec2f &value)
{
    _sfParams.setValue(value);
}


OSG_END_NAMESPACE

#define OSGPHYSICSCCYLINDERGEOMBASE_INLINE_CVSID "@(#)$Id: OSGPhysicsCCylinderGeomBase.inl,v 1.1 2005/10/21 15:44:24 a-m-z Exp $"
