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


#ifndef _OSGGEOPROPPTRS_H_
#define _OSGGEOPROPPTRS_H_
#ifdef __sgi
#pragma once
#endif

    #include <OSGGeoPropPositions.h>
#include <OSGGeoPropColors.h>
#include <OSGGeoPropNormals.h>
#include <OSGGeoPropTexCoords.h>
#include <OSGGeoPropIndices.h>
#include <OSGGeoPropPTypes.h>
#include <OSGGeoPropPLengths.h>

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*! \name                    Typedefs                                  */
/*! \{                                                                 */    

typedef GeoPosition3f::PtrType  GeoPosition3fPtr;

typedef GeoColor3f::PtrType     GeoColor3fPtr;
typedef GeoColor3ub::PtrType    GeoColor3ubPtr;
typedef GeoColor4ub::PtrType    GeoColor4ubPtr;

typedef GeoNormal3f::PtrType    GeoNormal3fPtr;

typedef GeoTexCoords2f::PtrType GeoTexCoords2fPtr;

typedef GeoIndexUI32::PtrType   GeoIndexUI32Ptr;

typedef GeoPTypeUI8::PtrType    GeoPTypeUI8Ptr;

typedef GeoPLengthUI32::PtrType GeoPLengthUI32Ptr;

/*! \}                                                                 */

OSG_END_NAMESPACE

#endif /* _OSGGEOPROPPTRS_H_ */
