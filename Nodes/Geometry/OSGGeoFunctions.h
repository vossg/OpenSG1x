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


#ifndef _OSGGEOFUNCTIONS_H_
#define _OSGGEOFUNCTIONS_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>
#include <OSGGeometryDef.h>
#include <OSGBaseTypes.h>
#include <OSGNode.h>


OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Functions
//---------------------------------------------------------------------------


/*! \brief calculate vertex normals for the geometry
 *  \ingroup Geometry
 */
OSG_GEOMETRY_DLLMAPPING void calcVertexNormals( GeometryPtr geo );

/*! \brief create a geometry that shows the normals of the geometry
 *  \ingroup Geometry
 */
OSG_GEOMETRY_DLLMAPPING NodePtr getNormals( GeometryPtr geo, Real32 length );


OSG_END_NAMESPACE

#endif /* _OSGGEOFUNCTIONS_H_ */
