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

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGNode.h>

OSG_BEGIN_NAMESPACE

//! \ingroup GeometryLib
//! Multi/Single index dictionary

struct IndexDic 
{
    typedef std::vector<Int32> Int32Vec;

  public:
  
          Int32     entry     (Int32Vec &indexVec);
    
    const Int32Vec &entry     (Int32     index   ); 

          UInt32    entryCount(void              ) const;

  private:
  
    std::map   <      Int32Vec  , Int32> _indexMap;
  
    std::vector<const Int32Vec *       > _indexVec;
 
};

	
/*--------------------------------------------------------------------------*/
/*! \name                     Geometry Functions                            */
/*! \{                                                                      */

/*! \brief calculate vertex normals for the geometry. 
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
void calcVertexNormals(GeometryPtr geo);

/*! \brief calculate vertex normals for the geometry, use creaseAngle to discrimnate
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
void calcVertexNormals( GeometryPtr geo,  Real32 creaseAngle );

/*! \brief calculate face normals for the geometry
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
void calcFaceNormals( GeometryPtr geo );

/*! \brief create the geometry index form the given FaceSet (VRML style) data 
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
Int32 setIndexFromVRMLData(      GeometryPtr    geo,
                            std::vector<Int32> &coordIndex,
                            std::vector<Int32> &normalIndex,
                            std::vector<Int32> &colorIndex,
                            std::vector<Int32> &texCoordIndex,
                                 bool           convex          = true,
                                 bool           ccw             = true,
                                 bool           normalPerVertex = true,
                                 bool           colorPerVertex  = true,
                                 bool           createNormal    = true,
                                 bool           faceSet         = true);


/*! \brief optimize the geo by creating strips and fans, 
 *  creates new index values but does not touch the property values
 *  returns the number of points to be transformed 
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
Int32 createOptimizedPrimitives (GeometryPtr geo,
                                 UInt32      iteration       = 1,
                                 bool        createStrips    = true,
                                 bool        createFans      = true,
                                 UInt32      minFanEdgeCount = 8,
                                 bool        colorCode       = false );

/*! \brief creates new index to share vertex property data
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
Int32 createSharedIndex ( GeometryPtr geo );

/*! \brief creates a single index geo from multi(interleave) geo.
 *  function will change (copy/resort) the property values.
 *  returns the number of property values
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
Int32 createSingleIndex ( GeometryPtr geo );

/*! \brief return the number of triangle/line/point elem 
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
UInt32 calcPrimitiveCount ( GeometryPtr geo,
                            UInt32 &triangle, UInt32 &line, UInt32 &point );

/*! \brief merge the given geometries into a minimal number of nodes
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
void mergeGeometries(std::vector<NodePtr> &nodes, 
                     std::vector<NodePtr> &results);


/*! \brief create a geometry that shows the normals of the geometry
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
NodePtr getNormals( GeometryPtr geo, Real32 length );


/*! \brief create a geometry that shows the face normals of another geometry
 *  \ingroup Geometry
 */
OSG_SYSTEMLIB_DLLMAPPING
NodePtr getFaceNormals(GeometryPtr geo, Real32 length);
/*! \}                                                                 */

OSG_END_NAMESPACE

#include <OSGGeoFunctions.inl>

#endif /* _OSGGEOFUNCTIONS_H_ */
