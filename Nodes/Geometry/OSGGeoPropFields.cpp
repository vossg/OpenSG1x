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

#define OSG_COMPILESYSTEMLIB
#define OSG_COMPILEGEOPROPFIELDINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGGeoPropFields.h>

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

#pragma instantiate SField             <GeoPositionPtr           >::_fieldType
#pragma instantiate SField             <GeoNormalPtr             >::_fieldType
#pragma instantiate SField             <GeoColorPtr              >::_fieldType
#pragma instantiate SField             <GeoTexCoordsPtr          >::_fieldType
#pragma instantiate SField             <GeoIndexPtr              >::_fieldType
#pragma instantiate SField             <GeoPTypePtr              >::_fieldType
#pragma instantiate SField             <GeoPLengthPtr            >::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, GeoPositionPtr , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoNormalPtr   , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoColorPtr    , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoTexCoordsPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoIndexPtr    , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoPTypePtr    , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoPLengthPtr  , OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE
