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

#define OSG_COMPILEGEOMETRY
#define OSG_COMPILEGEOPROPINST

#include "OSGGeoPropertyBase.h"

OSG_BEGIN_NAMESPACE

// explicit instantiation to work around compiler problems with static
// init for templated classes

#if 0
#ifdef OSG_NEED_EXPLICIT_INST_FOR_STATIC

template class OSG_GEOMETRY_DLLMAPPING 
     AbstractGeoProperty<GeoPositionPropertyDesc>;

template class OSG_GEOMETRY_DLLMAPPING GeoProperty<GeoPosition3fPropertyDesc>;

template class OSG_GEOMETRY_DLLMAPPING 
    AbstractGeoProperty<GeoNormalPropertyDesc>;

template class OSG_GEOMETRY_DLLMAPPING GeoProperty<GeoNormal3fPropertyDesc>;

template class OSG_GEOMETRY_DLLMAPPING GeoProperty<GeoTexCoord2fPropertyDesc>;

template class OSG_GEOMETRY_DLLMAPPING AbstractGeoProperty<
    GeoIndexPropertyDesc>;

template class OSG_GEOMETRY_DLLMAPPING GeoProperty<GeoIndexUI32PropertyDesc>;


template class OSG_GEOMETRY_DLLMAPPING GeoProperty<GeoPTypePropertyDesc>;
template class OSG_GEOMETRY_DLLMAPPING GeoProperty<GeoPLengthPropertyDesc>;

#endif
#endif

#if defined(__sgi)

#pragma instantiate AbstractGeoProperty<GeoPositionPropertyDesc  >::_type

#pragma instantiate AbstractGeoProperty<GeoNormalPropertyDesc    >::_type

#pragma instantiate AbstractGeoProperty<GeoColorPropertyDesc     >::_type

#pragma instantiate AbstractGeoProperty<GeoTexCoordsPropertyDesc >::_type

#pragma instantiate AbstractGeoProperty<GeoIndexPropertyDesc     >::_type

#pragma instantiate GeoProperty        <GeoPTypePropertyDesc     >::_type
#pragma instantiate GeoProperty        <GeoPTypePropertyDesc     >::_desc

#pragma instantiate GeoProperty        <GeoPLengthPropertyDesc   >::_type
#pragma instantiate GeoProperty        <GeoPLengthPropertyDesc   >::_desc

#else

OSG_ABSTR_FC_DLLEXPORT_DEF(AbstractGeoProperty, 
                           GeoPositionPropertyDesc, 
                           OSG_GEOMETRY_DLLTMPLMAPPING)

OSG_ABSTR_FC_DLLEXPORT_DEF(AbstractGeoProperty,
                           GeoNormalPropertyDesc, 
                           OSG_GEOMETRY_DLLTMPLMAPPING)

OSG_ABSTR_FC_DLLEXPORT_DEF(AbstractGeoProperty,
                           GeoColorPropertyDesc, 
                           OSG_GEOMETRY_DLLTMPLMAPPING)

OSG_ABSTR_FC_DLLEXPORT_DEF(AbstractGeoProperty,
                           GeoTexCoordPropertyDesc, 
                           OSG_GEOMETRY_DLLTMPLMAPPING)

OSG_ABSTR_FC_DLLEXPORT_DEF(AbstractGeoProperty,
                           GeoIndexPropertyDesc, 
                           OSG_GEOMETRY_DLLTMPLMAPPING)

OSG_FC_DLLEXPORT_DEF      (GeoProperty        ,
                           GeoPTypePropertyDesc, 
                           OSG_GEOMETRY_DLLTMPLMAPPING)

OSG_FC_DLLEXPORT_DEF      (GeoProperty        ,
                           GeoPLengthPropertyDesc, 
                           OSG_GEOMETRY_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE


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

