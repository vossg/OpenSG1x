/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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


#ifndef _OSGSIMPLEGEOMETRY_H_
#define _OSGSIMPLEGEOMETRY_H_
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

/*! \brief create a plane geometry
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING GeometryPtr makePlaneGeo(Real32 xsize, Real32 ysize,
                                                  UInt16 hor,   UInt16 vert);


/*! \brief create a plane
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING NodePtr makePlane(Real32 xsize, Real32 ysize,
                                           UInt16 hor,   UInt16 vert);

/*! \brief create a box geometry
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING GeometryPtr makeBoxGeo(Real32 xsize,
                                                Real32 ysize,
                                                Real32 zsize,
                                                UInt16 hor,
                                                UInt16 vert,
                                                UInt16 depth);

/*! \brief create a box geometry and node
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING NodePtr makeBox(Real32 xsize,
                                         Real32 ysize,
                                         Real32 zsize,
                                         UInt16 hor,
                                         UInt16 vert,
                                         UInt16 depth);

/*! \brief create a cone
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING GeometryPtr makeConeGeo(Real32 height,
                                                 Real32 botradius,
                                                 UInt16 sides,
                                                 bool   doSide,
                                                 bool   doBottom);

/*! \brief create a cone and node
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING NodePtr makeCone(Real32 height,
                                          Real32 botradius,
                                          UInt16 sides,
                                          bool   doSide,
                                          bool   doBottom);

/*! \brief create a cylinder
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING GeometryPtr makeCylinderGeo(Real32 height,
                                                     Real32 radius,
                                                     UInt16 sides,
                                                     bool   doSide,
                                                     bool   doTop,
                                                     bool   doBottom);

/*! \brief create a cylinder and node
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING NodePtr makeCylinder(Real32 height,
                                              Real32 radius,
                                              UInt16 sides,
                                              bool   doSide,
                                              bool   doTop,
                                              bool   doBottom);

/*! \brief create a torus
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING GeometryPtr makeTorusGeo( Real32 innerRadius,
                                           Real32 outerRadius,
                                           UInt16 sides, UInt16 rings );


/*! \brief create a torus and node
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING NodePtr makeTorus( Real32 innerRadius,
                                           Real32 outerRadius,
                                           UInt16 sides, UInt16 rings );

/*! \brief create a sphere
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING GeometryPtr makeSphereGeo(UInt16 depth,
                                                   Real32 radius);

/*! \brief create a sphere geometry and node
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING NodePtr makeSphere(UInt16 depth, Real32 radius);

/*! \brief create a sphere divided in latitude and longitude
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING GeometryPtr makeLatLongSphereGeo(UInt16 latres,
                                                          UInt16 longres,
                                                          Real32 radius);

/*! \brief create a sphere geometry divided in latitude and longitude and node
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING NodePtr makeLatLongSphere(UInt16 latres, 
                                                   UInt16 longres,
                                                   Real32 radius);

/*! \brief create a conical frustum
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING GeometryPtr makeConicalFrustumGeo(Real32 height,
                                                           Real32 topradius,
                                                           Real32 botradius,
                                                           UInt16 sides,
                                                           bool   doSide,
                                                           bool   doTop,
                                                           bool   doBottom);

/*! \brief create a conical frustum and node
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING NodePtr makeConicalFrustum(Real32 height,
                                                    Real32 topradius,
                                                    Real32 botradius,
                                                    UInt16 sides,
                                                    bool   doSide,
                                                    bool   doTop,
                                                    bool   doBottom);

OSG_SYSTEMLIB_DLLMAPPING GeoPositions3fPtr makeGeoPositions3fPtr(UInt32 uiSize);
OSG_SYSTEMLIB_DLLMAPPING GeoIndicesUI32Ptr makeGeoIndicesUI32Ptr(UInt32 uiSize);
OSG_SYSTEMLIB_DLLMAPPING GeoPLengthsPtr    makeGeoPLengthsPtr   (UInt32 uiSize);
OSG_SYSTEMLIB_DLLMAPPING GeoPTypesPtr      makeGeoPTypesPtr     (UInt32 uiSize);

/*! \brief access the default materials
 *  \ingroup SimpleGeometry
 */
OSG_SYSTEMLIB_DLLMAPPING MaterialPtr getDefaultMaterial(void);

OSG_SYSTEMLIB_DLLMAPPING MaterialPtr getDefaultUnlitMaterial(void);


/*! \}                                                                 */

OSG_END_NAMESPACE

#endif /* _OSGSIMPLEGEOMETRY_H_ */
