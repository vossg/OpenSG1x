/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGNode.h>
#include <OSGGeometryDef.h>


OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Functions
//---------------------------------------------------------------------------


/*! \brief create a plane
 *  \ingroup SimpleGeometry
 */
OSG_GEOMETRY_DLLMAPPING NodePtr makePlane(Real32 xsize, Real32 ysize, 
                                		  UInt16 hor,   UInt16 vert);


/*! \brief create a box
 *  \ingroup SimpleGeometry
 */
OSG_GEOMETRY_DLLMAPPING NodePtr makeBox( Real32 xsize, Real32 ysize, Real32 zsize, 
										 UInt16 hor,   UInt16 vert,  UInt16 depth);


/*! \brief create a cone
 *  \ingroup SimpleGeometry
 */
OSG_GEOMETRY_DLLMAPPING NodePtr makeCone( Real32 height,
		Real32 botradius, UInt16 sides, Bool doSide, Bool doBottom );

/*! \brief create a cylinder
 *  \ingroup SimpleGeometry
 */
OSG_GEOMETRY_DLLMAPPING NodePtr makeCylinder( Real32 height,
		Real32 radius, UInt16 sides, Bool doSide, Bool doTop, Bool doBottom );

/*! \brief create a torus
 *  \ingroup SimpleGeometry
 */
OSG_GEOMETRY_DLLMAPPING NodePtr makeTorus( Real32 innerRadius, 
										   Real32 outerRadius, 
										   UInt16 sides, UInt16 rings );

/*! \brief create a sphere
 *  \ingroup SimpleGeometry
 */
OSG_GEOMETRY_DLLMAPPING NodePtr makeSphere( UInt16 depth, Real32 radius );

/*! \brief create a conical frustum
 *  \ingroup SimpleGeometry
 */
OSG_GEOMETRY_DLLMAPPING NodePtr makeConicalFrustum( Real32 height,
		Real32 topradius, Real32 botradius, UInt16 sides, 
		Bool doSide, Bool doTop, Bool doBottom );

OSG_END_NAMESPACE

#endif /* _OSGSIMPLEGEOMETRY_H_ */
