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


#ifndef _OSGGEOPROPPTRS_H_
#define _OSGGEOPROPPTRS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGGeoPropertyBase.h>
#include <OSGGeoPropPositions.h>
#include <OSGGeoPropColors.h>
#include <OSGGeoPropNormals.h>
#include <OSGGeoPropTexCoords.h>
#include <OSGGeoPropIndices.h>
#include <OSGGeoPropPTypes.h>
#include <OSGGeoPropPLengths.h>

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*! \name               Pointer Typedefs                               */
/*! \{                                                                 */    

typedef GeoPositions2s::PtrType  GeoPositions2sPtr;
typedef GeoPositions3s::PtrType  GeoPositions3sPtr;
typedef GeoPositions4s::PtrType  GeoPositions4sPtr;

typedef GeoPositions2f::PtrType  GeoPositions2fPtr;
typedef GeoPositions3f::PtrType  GeoPositions3fPtr;
typedef GeoPositions4f::PtrType  GeoPositions4fPtr;

typedef GeoPositions2d::PtrType  GeoPositions2dPtr;
typedef GeoPositions3d::PtrType  GeoPositions3dPtr;
typedef GeoPositions4d::PtrType  GeoPositions4dPtr;

typedef GeoColors3f::PtrType     GeoColors3fPtr;
typedef GeoColors3ub::PtrType    GeoColors3ubPtr;
typedef GeoColors4f::PtrType     GeoColors4fPtr;
typedef GeoColors4ub::PtrType    GeoColors4ubPtr;

typedef GeoNormals3f::PtrType    GeoNormals3fPtr;
typedef GeoNormals3s::PtrType    GeoNormals3sPtr;
#ifndef OSG_NO_INT8_PNT
typedef GeoNormals3b::PtrType    GeoNormals3bPtr;
#endif

typedef GeoTexCoords1f::PtrType  GeoTexCoords1fPtr;
typedef GeoTexCoords2f::PtrType  GeoTexCoords2fPtr;
typedef GeoTexCoords3f::PtrType  GeoTexCoords3fPtr;
typedef GeoTexCoords4f::PtrType  GeoTexCoords4fPtr;

typedef GeoTexCoords1d::PtrType  GeoTexCoords1dPtr;
typedef GeoTexCoords2d::PtrType  GeoTexCoords2dPtr;
typedef GeoTexCoords3d::PtrType  GeoTexCoords3dPtr;
typedef GeoTexCoords4d::PtrType  GeoTexCoords4dPtr;

typedef GeoIndicesUI32::PtrType  GeoIndicesUI32Ptr;
typedef GeoIndicesUI16::PtrType  GeoIndicesUI16Ptr;

typedef GeoPTypesUI8::PtrType    GeoPTypesUI8Ptr;

typedef GeoPLengthsUI32::PtrType GeoPLengthsUI32Ptr;
typedef GeoPLengthsUI16::PtrType GeoPLengthsUI16Ptr;
typedef GeoPLengthsUI8::PtrType  GeoPLengthsUI8Ptr;

/*! \}                                                                 */

OSG_END_NAMESPACE

#endif /* _OSGGEOPROPPTRS_H_ */
