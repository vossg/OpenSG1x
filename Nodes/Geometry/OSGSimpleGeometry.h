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
#include <OSGGeometryBase.h>


OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Functions
//---------------------------------------------------------------------------

OSG_GEOMETRY_DLLMAPPING NodePtr makePlane(Real32 xsize, Real32 ysize, 
                                		  UInt16 hor,   UInt16 vert);


OSG_GEOMETRY_DLLMAPPING NodePtr makeCone( Real32 height, Real32 radius, 
										  UInt16 sides );

OSG_GEOMETRY_DLLMAPPING NodePtr makeTorus( Real32 innerRadius, 
										   Real32 outerRadius, 
										   UInt16 sides, UInt16 rings );

OSG_GEOMETRY_DLLMAPPING NodePtr makeSphere( UInt16 depth, Real32 radius );

OSG_END_NAMESPACE

#endif /* _OSGSIMPLEGEOMETRY_H_ */
