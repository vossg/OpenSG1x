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

#include "OSGConfig.h"

#include "new.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEBASE

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

DynamicVolume::DynamicVolume(const DynamicVolume &obj) :
    _type(obj._type)
{
	switch ( _type ) 
	{
        case BOX_VOLUME:
            new (_volumeMem) 
               BoxVolume(*((OSG::BoxVolume*)(obj._volumeMem)));
		break;
        
        case SPHERE_VOLUME:
            new (_volumeMem) 
               SphereVolume(*((OSG::SphereVolume*)(obj._volumeMem)));
		break;

        case CYLINDER_VOLUME:
            new (_volumeMem)
               CylinderVolume(*((OSG::CylinderVolume*)(obj._volumeMem)));
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
	case CYLINDER_VOLUME:
		new (_volumeMem) CylinderVolume;
		break;
	}
}

void DynamicVolume::morphToType ( Type type )
{
	// TODO optimize;

	switch (getType()) {
	case BOX_VOLUME:
		new (_volumeMem) BoxVolume;
		break;
	case SPHERE_VOLUME:
		new (_volumeMem) SphereVolume;
		break;
	case CYLINDER_VOLUME:
		new (_volumeMem) CylinderVolume;
		break;
	}
}
		
OSG_BASE_DLLMAPPING
ostream &OSG::operator <<(ostream &outStream,
                          const DynamicVolume &vol)
{
    return outStream << "DynVol << NI ";
}

DynamicVolume & DynamicVolume::operator = (const DynamicVolume &source)
{
	_type = source._type;

	switch ( _type ) 
	{
	case BOX_VOLUME:
		new (_volumeMem) BoxVolume( *((OSG::BoxVolume*)(source._volumeMem)) );
		break;
	case SPHERE_VOLUME:
		new (_volumeMem) SphereVolume( *((OSG::SphereVolume*)(source._volumeMem)) );
		break;
	case CYLINDER_VOLUME:
		new (_volumeMem) CylinderVolume( *((OSG::CylinderVolume*)(source._volumeMem)) );
		break;
	}	
	
	return *this;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
