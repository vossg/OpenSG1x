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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

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

static char cvsid[] = "@(#)$Id: OSGGeoFunctions.cpp,v 1.6 2001/07/23 11:14:06 dirk Exp $";

#ifdef __sgi
#pragma reset woff 1174
#endif



/*! \ingroup Geometry
	\param geo	the geometry to work on

calcVertexNormals calculates the normals for the geometry's vertices. It
does this simply by accumulating the face normals of all triangles that
use the vertex and renormalizing. 

*/

OSG_SYSTEMLIB_DLLMAPPING
void osg::calcVertexNormals( GeometryPtr geo )
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
	
	beginEditCP(geo, Geometry::NormalsFieldMask | Geometry::IndexMappingFieldMask );
	geo->setNormals( norms );

    	MFUInt16 &im = geo->getIndexMapping();
    	if ( im.size() > 0 )
	{
	    Int16 pi,ni;
	    pi = geo->calcMappingIndex( Geometry::MapPosition );
	    ni = geo->calcMappingIndex( Geometry::MapNormal );

	    if ( ni )
		im.setValue( im.getValue(ni) & ~ Geometry::MapNormal, ni );
	    if ( pi >= 0 )
		im.setValue( im.getValue(pi) |   Geometry::MapNormal, pi );
	}
	
	endEditCP( geo );
}


/*! \ingroup Geometry
	\param geo		the geometry to work on
	\param length	the length of the normal vectors

getNormals creates a geometry that consists of the normals of \a geo
as lines. Every line starts of the position the normals is associated
with (vertex for vertex normals, center of face for face normals) and
has the length \a length.

*/
OSG_SYSTEMLIB_DLLMAPPING NodePtr osg::getNormals(GeometryPtr geo, 
                                                 Real32      length)
{
    NodePtr  p = Node::create();
    GeometryPtr g = Geometry::create();
	GeoPosition3f::PtrType pnts = GeoPosition3f::create();
	GeoIndexUI32Ptr index = GeoIndexUI32::create();	
	GeoPTypePtr type = GeoPType::create();	
	GeoPLengthPtr lens = GeoPLength::create();	

	// calculate
	beginEditCP(pnts);

	PrimitiveIterator pi(geo);
	
	if ( 1 /* no easy way to check right now */ )
	{
		for ( pi  = geo->beginPrimitives(); 
			  pi != geo->endPrimitives(); ++pi )
		{
			for ( UInt16 k = 0; k < pi.getLength(); k++ )
			{
				pnts->addValue( pi.getPosition( k ) );
				pnts->addValue( pi.getPosition( k ) + 
									length * pi.getNormal( k ) );
			}	
		}
	}
	else
	{
		Pnt3f center(0,0,0);
		
		for ( pi  = geo->beginPrimitives(); 
			  pi != geo->endPrimitives(); ++pi )
		{
			for ( UInt16 k = 0; k < pi.getLength(); k++ )
			{
				center[0] += pi.getPosition( k )[0];
				center[1] += pi.getPosition( k )[1];
				center[2] += pi.getPosition( k )[2];
			}
			pnts->addValue( center );
			pnts->addValue( center +  length * pi.getNormal( 0 ) );
		}
	}

	endEditCP(pnts);
	
	// create the geometry
	beginEditCP(index);
	for ( UInt32 i = 0; i < pnts->getSize(); i++ )
		index->addValue( i );
	endEditCP(index);

	beginEditCP(type);
	type->addValue( GL_LINES );
	endEditCP(type);

	beginEditCP(lens);
	lens->addValue( index->getSize() );
	endEditCP(lens);
	
	beginEditCP(g);
	g->setTypes( type );
	g->setLengths( lens );
	g->setIndex( index );
	g->setPositions( pnts );
	endEditCP(g);
	
	beginEditCP(p);
	p->setCore(g);
	endEditCP(p);
	
	return p;
}
