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

#define OSG_COMPILEGEOPROPFIELDINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGGeoPropFields.h>

OSG_BEGIN_NAMESPACE

DataType FieldDataTraits<GeoPositionsPtr >::_type("GeoPositionsPtr",
                                                 "GeoPositionsInterfacePtr",
                                                 true);
DataType FieldDataTraits<GeoNormalsPtr   >::_type("GeoNormalsPtr",
                                                 "GeoNormalsInterfacePtr",
                                                 true);
DataType FieldDataTraits<GeoColorsPtr    >::_type("GeoColorsPtr",
                                                 "GeoColorsInterfacePtr",
                                                 true);
DataType FieldDataTraits<GeoTexCoordsPtr>::_type("GeoTexCoordsPtr",
                                                 "GeoTexCoordsInterfacePtr",
                                                 true);
DataType FieldDataTraits<GeoIndicesPtr    >::_type("GeoIndicesPtr",
                                                 "GeoIndicesInterfacePtr",
                                                 true);
DataType FieldDataTraits<GeoPTypesPtr    >::_type("GeoPTypesPtr",
                                                 "GeoPTypesInterfacePtr",
                                                 true);
DataType FieldDataTraits<GeoPLengthsPtr  >::_type("GeoPLengthsPtr",
                                                 "GeoPLengthsInterfacePtr",
                                                 true);

#if defined(__sgi)

#pragma instantiate SField             <GeoPositionsPtr           >::_fieldType
#pragma instantiate SField             <GeoNormalsPtr             >::_fieldType
#pragma instantiate SField             <GeoColorsPtr              >::_fieldType
#pragma instantiate SField             <GeoTexCoordsPtr          >::_fieldType
#pragma instantiate SField             <GeoIndicesPtr              >::_fieldType
#pragma instantiate SField             <GeoPTypesPtr              >::_fieldType
#pragma instantiate SField             <GeoPLengthsPtr            >::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, GeoPositionsPtr , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoNormalsPtr   , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoColorsPtr    , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoTexCoordsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoIndicesPtr    , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoPTypesPtr    , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoPLengthsPtr  , OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE
