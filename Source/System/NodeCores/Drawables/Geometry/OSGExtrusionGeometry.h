/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *               Andreas Fischle, Bastian Grundel                            *
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

#ifndef _OSGEXTRUSIONGEOMETRY_H_
#define _OSGEXTRUSIONGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGQuaternion.h>
#include <OSGNode.h>
#include <OSGSystemDef.h>
#include <OSGGeoPropPtrs.h>
#include <OSGGeometry.h>

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*! \name                   Construction functions                     */
/*! \{                                                                 */


/*! \brief create a extrusion
 *  \ingroup ExtrusionGeometry
 */

OSG_SYSTEMLIB_DLLMAPPING 
NodePtr makeExtrusion(const std::vector<Vec2f     > &crossSection,
                      const std::vector<Quaternion> &orientation,
                      const std::vector<Vec2f     > &scale,
                      const std::vector<Vec3f     > &spine,
                                 bool                beginCap,
                                 bool                endCap,
                                 bool                ccw,
                                 bool                convex,
                                 bool                buildNormal,
                                 bool                buildTexCoord,
                                 UInt32              numOfSubdivision);  

/*! \brief create a extrusion and node
 *  \ingroup ExtrusionGeometry
 */

OSG_SYSTEMLIB_DLLMAPPING
GeometryPtr makeExtrusionGeo(const std::vector<Vec2f     > &crossSection,
                             const std::vector<Quaternion> &orientation,
                             const std::vector<Vec2f     > &scale,
                             const std::vector<Vec3f     > &spine,
                                        bool                beginCap,
                                        bool                endCap,
                                        bool                ccw,
                                        bool                convex,
                                        bool                buildNormal,
                                        bool                buildTexCoord,
                                        UInt32              numOfSubdivision);


OSG_END_NAMESPACE

#endif /* _OSGEXTRUSIONGEOMETRY_H_ */
