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


#ifndef _OSGGEOFUNCTIONS_H_
#define _OSGGEOFUNCTIONS_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGNode.h>


OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Functions
//---------------------------------------------------------------------------


/*! \brief calculate vertex normals for the geometry
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING void calcVertexNormals( GeometryPtr geo );

/*! \brief create a geometry that shows the normals of the geometry
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING NodePtr getNormals( GeometryPtr geo, Real32 length );

/*! \brief create the geometry index form the given FaceSet (VRML style) data 
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING 
Int32 setIndexFromVRMLData ( GeometryPtr geo, 
                             vector<Int32> & coordIndex,
                             vector<Int32> & normalIndex,
                             vector<Int32> & colorIndex,
                             vector<Int32> & texCoordIndex,
                             Bool convex = true, 
                             Bool ccw = true,
                             Bool normalPerVertex = true,
                             Bool colorPerVertex = true,
                             Bool createNormal = true,
                             Bool faceSet = true );


/*! \brief optimize the geo by creating strips and fans, 
 *  creates new index values but does not touch the property values
 *  returns the number of points to be transformed 
 *  \ingroup Geometry
 */
Int32 createOptimizedPrimitives ( GeometryPtr geo,
                                  UInt32 iteration = 1,
                                  Bool createStrips = true, 
                                  Bool createFans = true,
                                  UInt32 minFanEdgeCount = 8, 
                                  Bool colorCode = false );

/*! \brief return the number of triangle/line/point elem 
 *  \ingroup Geometry
 */
UInt32 calcPrimitiveCount ( GeometryPtr geo,
                            UInt32 &triangle, UInt32 &line, UInt32 &point);

/*! \brief merge the given geometries into a minimal number of nodes
 *  \ingroup Geometry
 */
void mergeGeometries( vector<NodePtr> & nodes, vector<NodePtr> & results );


/*! \brief calculate face normals for the geometry
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING 
void calcFaceNormals( GeometryPtr geo );

/*! \brief create a geometry that shows the face normals of another geometry
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
NodePtr getFaceNormals(GeometryPtr geo, Real32 length);

OSG_END_NAMESPACE

#endif /* _OSGGEOFUNCTIONS_H_ */
