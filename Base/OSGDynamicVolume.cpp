/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include "OSGConfig.h"

#include "new.h"

// Class declarations
#include "OSGDynamicVolume.h"
#include "OSGBoxVolume.h"
#include "OSGSphereVolume.h"
#include "OSGCylinderVolume.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------- constructor ----------------------------------*/

DynamicVolume::DynamicVolume ( Type type)
{
    setVolumeType(type);
}

DynamicVolume::DynamicVolume(const DynamicVolume &obj)
    : Volume(obj),
    _type(obj._type)
{
    switch ( _type ) {
    case BOX_VOLUME:
        new (_volumeMem) BoxVolume(*((OSG::BoxVolume*)(obj._volumeMem)));
        break;
    case SPHERE_VOLUME:
        new (_volumeMem) SphereVolume(*((OSG::SphereVolume*)(obj._volumeMem)));
        break;
    }
}

/*------------------------------ feature ----------------------------------*/

void DynamicVolume::setVolumeType ( Type type )
{
    _type = type;

    switch (type) {
    case BOX_VOLUME:
        new (_volumeMem) BoxVolume;
        break;
    case SPHERE_VOLUME:
        new (_volumeMem) SphereVolume;
        break;
    }
}

void DynamicVolume::morphToType ( Type type )
{
    Pnt3f min,max;
    Vec3f vec;
    BoxVolume *bv;
    SphereVolume *sv;

    if (type == _type)
        return;
    else
        switch (getType()) {
        case BOX_VOLUME:
            getBounds(min,max);
            bv = new (_volumeMem) BoxVolume;
            bv->setBounds(min,max);
            break;
        case SPHERE_VOLUME:
            getBounds(min,max);
            sv = new (_volumeMem) SphereVolume;
            vec.setValues(max.x(),max.y(),max.z());
            vec -= Vec3f(min.x(),min.y(),min.z());
            sv->setValue(vec,vec.length()/2);
            break;
        }
}

DynamicVolume & DynamicVolume::operator = (const DynamicVolume &source)
{
    _type = source._type;

    switch ( _type )
    {
    case BOX_VOLUME:
        new (_volumeMem)BoxVolume( *((OSG::BoxVolume*)(source._volumeMem)));
        break;
    case SPHERE_VOLUME:
        new (_volumeMem)SphereVolume(*((OSG::SphereVolume*)
            (source._volumeMem)));
        break;
    }

    return *this;
}

/// print the volume */
void DynamicVolume::dump(UInt32 uiIndent, const BitVector bvFlags) const
{
    PLOG << "Dyn:";

    getInstance().dump(uiIndent, bvFlags);
}

bool DynamicVolume::operator ==(
    const DynamicVolume &OSG_CHECK_ARG(other)) const
{
    return false; 
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
