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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEGEOMETRY

#include <OSGGeometryBase.h>

#include <OSGLog.h>

#include "OSGGeometry.h"
#include "OSGGeoPropPtrs.h"
#include "OSGTriangleIterator.h"
#include "OSGGeoFunctions.h"

OSG_USING_NAMESPACE



/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

#ifdef __sgi
#pragma set woff 1174
#endif

static char cvsid[] = "@(#)$Id: OSGGeoFunctions.cpp,v 1.2 2001/02/15 10:09:42 vossg Exp $";

#ifdef __sgi
#pragma reset woff 1174
#endif



/*! \ingroup Geometry
	\param geo	the geometry to work on

calcVertexNormals calculates the normals for the geometry's vertices. It
does this simply by accumulating the face normals of all triangles that
use the vertex and renormalizing. 

*/

OSG_GEOMETRY_DLLMAPPING
void osg::calcVertexNormals( GeometryPtr& geo )
{
	GeoNormalPtr norms;
    int          i;

	if ( geo->getNormals() == GeoNormal3fPtr::NullPtr )
	{
		norms = GeoNormal3f::create();
	}
	else
		norms = geo->getNormals();
	
	beginEditCP(norms);

	norms->resize( geo->getPositions()->getSize() );

	for ( i = 0; i < geo->getPositions()->getSize(); i++ )
	{
		norms->setValue( Vec3f( 0,0,0 ), i );
	}

	for ( TriangleIterator t = geo->beginTriangles(); t != geo->endTriangles(); ++t )
	{
		Plane p( t.getPosition(0), t.getPosition(1), t.getPosition(2) );
		
		norms->setValue( norms->getValue( t.getPositionIndex(0) ) + p.getNormal(), 
						 t.getPositionIndex(0) ); 
		norms->setValue( norms->getValue( t.getPositionIndex(1) ) + p.getNormal(), 
						 t.getPositionIndex(1) ); 
		norms->setValue( norms->getValue( t.getPositionIndex(2) ) + p.getNormal(), 
						 t.getPositionIndex(2) ); 
	}

	for ( i = 0; i < geo->getPositions()->getSize(); i++ )
	{
		Vec3f n = norms->getValue( i );
		n.normalize();
		norms->setValue( n, i );
	}

	endEditCP(norms);
	
	beginEditCP(geo, Geometry::NormalsFieldMask | Geometry::NormalPerVertexFieldMask );
	geo->setNormals( norms );
	geo->setNormalPerVertex( true );
	endEditCP( geo );
}
