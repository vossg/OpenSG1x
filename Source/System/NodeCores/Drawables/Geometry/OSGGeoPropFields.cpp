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

#define OSG_COMPILEGEOPROPFIELDINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGGeoPropFields.h>

#include <OSGMFieldTypeDef.inl>
#include <OSGSFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

// Doxygen can't find these
#ifndef OSG_DO_DOC

DataType FieldDataTraits<GeoPositionsPtr>::_type("GeoPositionsPtr",
                                                 "GeoPositionsInterfacePtr");
DataType FieldDataTraits<GeoNormalsPtr  >::_type("GeoNormalsPtr",
                                                 "GeoNormalsInterfacePtr");
DataType FieldDataTraits<GeoColorsPtr   >::_type("GeoColorsPtr",
                                                 "GeoColorsInterfacePtr");
DataType FieldDataTraits<GeoTexCoordsPtr>::_type("GeoTexCoordsPtr",
                                                 "GeoTexCoordsInterfacePtr");
DataType FieldDataTraits<GeoIndicesPtr  >::_type("GeoIndicesPtr",
                                                 "GeoIndicesInterfacePtr");
DataType FieldDataTraits<GeoPTypesPtr   >::_type("GeoPTypesPtr",
                                                 "GeoPTypesInterfacePtr");
DataType FieldDataTraits<GeoPLengthsPtr >::_type("GeoPLengthsPtr",
                                                 "GeoPLengthsInterfacePtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(GeoPositionsPtr , OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(GeoNormalsPtr   , OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(GeoColorsPtr    , OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(GeoTexCoordsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(GeoIndicesPtr    , OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(GeoPTypesPtr    , OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(GeoPLengthsPtr  , OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_DLLEXPORT_MFIELD_DEF1(GeoPositionsPtr , OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(GeoNormalsPtr   , OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(GeoColorsPtr    , OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(GeoTexCoordsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(GeoIndicesPtr    , OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(GeoPTypesPtr    , OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(GeoPLengthsPtr  , OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE
