/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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


#ifndef _OSGGeoSimpleGeometry_H_
#define _OSGGeoSimpleGeometry_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGNode.h>
#include <OSGSystemDef.h>
#include <OSGGeoPropPtrs.h>
#include <OSGGeometry.h>
#include <OSGMaterial.h>


OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*! \name                   Construction functions                     */
/*! \{                                                                 */

OSG_SYSTEMLIB_DLLMAPPING 
GeometryPtr               makePlaneGeo          (Real32 xsize, 
                                                 Real32 ysize,
                                                 UInt16 hor,   
                                                 UInt16 vert);

OSG_SYSTEMLIB_DLLMAPPING 
NodePtr                   makePlane             (Real32 xsize, 
                                                 Real32 ysize,
                                                 UInt16 hor,   
                                                 UInt16 vert);

OSG_SYSTEMLIB_DLLMAPPING 
GeometryPtr               makeBoxGeo            (Real32 xsize,
                                                 Real32 ysize,
                                                 Real32 zsize,
                                                 UInt16 hor,
                                                 UInt16 vert,
                                                 UInt16 depth);

OSG_SYSTEMLIB_DLLMAPPING 
NodePtr                   makeBox               (Real32 xsize,
                                                 Real32 ysize,
                                                 Real32 zsize,
                                                 UInt16 hor,
                                                 UInt16 vert,
                                                 UInt16 depth);

OSG_SYSTEMLIB_DLLMAPPING 
GeometryPtr               makeConeGeo           (Real32 height,
                                                 Real32 botradius,
                                                 UInt16 sides,
                                                 bool   doSide,
                                                 bool   doBottom);

OSG_SYSTEMLIB_DLLMAPPING 
NodePtr                   makeCone              (Real32 height,
                                                 Real32 botradius,
                                                 UInt16 sides,
                                                 bool   doSide,
                                                 bool   doBottom);

OSG_SYSTEMLIB_DLLMAPPING 
GeometryPtr               makeCylinderGeo       (Real32 height,
                                                 Real32 radius,
                                                 UInt16 sides,
                                                 bool   doSide,
                                                 bool   doTop,
                                                 bool   doBottom);

OSG_SYSTEMLIB_DLLMAPPING 
NodePtr                   makeCylinder          (Real32 height,
                                                 Real32 radius,
                                                 UInt16 sides,
                                                 bool   doSide,
                                                 bool   doTop,
                                                 bool   doBottom);

OSG_SYSTEMLIB_DLLMAPPING 
GeometryPtr               makeTorusGeo          (Real32 innerRadius,
                                                 Real32 outerRadius,
                                                 UInt16 sides, 
                                                 UInt16 rings );


OSG_SYSTEMLIB_DLLMAPPING 
NodePtr                   makeTorus             (Real32 innerRadius,
                                                 Real32 outerRadius,
                                                 UInt16 sides, 
                                                 UInt16 rings);

OSG_SYSTEMLIB_DLLMAPPING 
GeometryPtr               makeSphereGeo         (UInt16 depth,
                                                 Real32 radius);

OSG_SYSTEMLIB_DLLMAPPING 
NodePtr                   makeSphere            (UInt16 depth, 
                                                 Real32 radius);

OSG_SYSTEMLIB_DLLMAPPING 
GeometryPtr               makeLatLongSphereGeo  (UInt16 latres,
                                                 UInt16 longres,
                                                 Real32 radius);

OSG_SYSTEMLIB_DLLMAPPING 
NodePtr                   makeLatLongSphere     (UInt16 latres, 
                                                 UInt16 longres,
                                                 Real32 radius);

OSG_SYSTEMLIB_DLLMAPPING 
GeometryPtr               makeConicalFrustumGeo (Real32 height,
                                                 Real32 topradius,
                                                 Real32 botradius,
                                                 UInt16 sides,
                                                 bool   doSide,
                                                 bool   doTop,
                                                 bool   doBottom);

OSG_SYSTEMLIB_DLLMAPPING 
NodePtr                   makeConicalFrustum    (Real32 height,
                                                 Real32 topradius,
                                                 Real32 botradius,
                                                 UInt16 sides,
                                                 bool   doSide,
                                                 bool   doTop,
                                                 bool   doBottom);

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name                     Material Access                          */
/*! \{                                                                 */

OSG_SYSTEMLIB_DLLMAPPING MaterialPtr getDefaultMaterial(void);

OSG_SYSTEMLIB_DLLMAPPING MaterialPtr getDefaultUnlitMaterial(void);

/*! \}                                                                 */

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

/*! \brief some workaround functions for Windows problems
 *  \ingroup GrpSystemDrawablesGeometrySimpleGeometry
 */

OSG_SYSTEMLIB_DLLMAPPING GeoPositions3fPtr makeGeoPositions3fPtr(UInt32 uiSize);
OSG_SYSTEMLIB_DLLMAPPING GeoIndicesUI32Ptr makeGeoIndicesUI32Ptr(UInt32 uiSize);
OSG_SYSTEMLIB_DLLMAPPING GeoPLengthsPtr    makeGeoPLengthsPtr   (UInt32 uiSize);
OSG_SYSTEMLIB_DLLMAPPING GeoPTypesPtr      makeGeoPTypesPtr     (UInt32 uiSize);

#endif            // exclude from doc


OSG_END_NAMESPACE

#endif /* _OSGGeoSimpleGeometry_H_ */
