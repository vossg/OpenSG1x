/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#define OSG_COMPILEGEOPROPINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGGeoPropertyBase.h"

OSG_USING_NAMESPACE

OSG_GEO_PROP_TYPE_TMPL_DEF(AbstractGeoProperty, GeoPropertyDesc, PtrType)

OSG_BEGIN_NAMESPACE

OSG_ABSTR_GEOPROP_DLLEXPORT_DEF(AbstractGeoProperty, 
                                GeoPositionsPropertyDesc, 
                                OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_ABSTR_GEOPROP_DLLEXPORT_DEF(AbstractGeoProperty,
                                GeoNormalsPropertyDesc, 
                                OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_ABSTR_GEOPROP_DLLEXPORT_DEF(AbstractGeoProperty,
                                GeoColorsPropertyDesc, 
                                OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_ABSTR_GEOPROP_DLLEXPORT_DEF(AbstractGeoProperty,
                                GeoTexCoordsPropertyDesc, 
                                OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_ABSTR_GEOPROP_DLLEXPORT_DEF(AbstractGeoProperty,
                                GeoIndicesPropertyDesc, 
                                OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_ABSTR_GEOPROP_DLLEXPORT_DEF(AbstractGeoProperty,
                                GeoPTypesPropertyDesc, 
                                OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_ABSTR_GEOPROP_DLLEXPORT_DEF(AbstractGeoProperty,
                                GeoPLengthsPropertyDesc, 
                                OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE


///---------------------------------------------------------------------------
//  FUNCTION: 
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

