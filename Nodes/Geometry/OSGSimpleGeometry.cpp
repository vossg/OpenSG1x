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

#include "OSGSimpleGeometry.h"
#include "OSGGeometry.h"
#include "OSGGeoPropPtrs.h"

OSG_USING_NAMESPACE



/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \defgroup SimpleGeometry
	\ingroup GeometryLib

SimpleGeometry combines a number of functions to create some spezialized 
geometry very easily. 

*/

#ifdef __sgi
#pragma set woff 1174
#endif

static char cvsid[] = "@(#)$Id: $";

#ifdef __sgi
#pragma reset woff 1174
#endif



/*! \ingroup SimpleGeometry
	\return NodePtr the created plane
	\param xsize	the plane's size in the x direction
	\param ysize	the plane's size in the y direction
	\param hor		number of subdivisons in the x direction
	\param vert		number of subdivisons in the y direction

makePlane creates a plane in the x/y plane. It spans the [-\a xsize /2,\a xsize /2]x
[-\a ysize /2,\a ysize/2] area and is subdivided into \a hor * \a vert quads.

*/

OSG_GEOMETRY_DLLMAPPING
NodePtr OSG::makePlane( Real32 xsize, Real32 ysize, UInt16 hor, UInt16 vert )
{
	if ( ! hor || ! vert )
	{
		SWARNING << "makePlane: illegal parameters hor=" << hor << ", vert="
				 << vert << endl;
		return NullNode;
	}
	
	GeoPosition3fPtr    pnts  = GeoPosition3f::create();
	GeoNormal3fPtr		norms = GeoNormal3f::create();
	GeoIndexUI32Ptr		index = GeoIndexUI32::create();	
	GeoPLengthPtr		lens  = GeoPLength::create();	
	GeoPTypePtr			types = GeoPType::create();	
	
	UInt16 x,y;
	Real32 xstep,ystep;
	xstep = xsize / hor;
	ystep = ysize / vert;

	// calc the vertices

	GeoPosition3f::FieldType * p = pnts->getFieldPtr();
	GeoNormal3f::FieldType   * n = norms->getFieldPtr();

	beginEditCP(pnts);
	beginEditCP(norms);
	
	for ( y = 0; y <= vert; y++ )
	{
		for ( x = 0; x <= hor; x++ )
		{
			p->addValue( Pnt3f( x * xstep - xsize / 2, y * ystep - ysize / 2, 0 ) );
			n->addValue( Vec3f( 0, 0, 1) );
		}
	}

	endEditCP(pnts);
	endEditCP(norms);

	// create the faces
	
	GeoIndexUI32::FieldType * i = index->getFieldPtr();
	GeoPLength::FieldType   * l = lens->getFieldPtr();
	GeoPType::FieldType     * t = types->getFieldPtr();

	beginEditCP(index);
	beginEditCP(lens);
	beginEditCP(types);

	for ( y = 0; y < vert; y++ )
	{
		t->addValue( GL_TRIANGLE_STRIP );
		l->addValue( 2 * ( hor + 1 ) );
		
		for ( x = 0; x <= hor; x++ )
		{
			i->addValue(   y      * ( hor + 1 ) + x );
			i->addValue( ( y + 1) * ( hor + 1 ) + x );
		}
	}

	endEditCP(index);
	endEditCP(lens);
	endEditCP(types);
	
	// create the geometry
	
    GeometryPtr geo = Geometry::create();

 	beginEditCP(geo);
	geo->setPositions( pnts );
	geo->setNormals( norms );
	geo->setNormalPerVertex( true );
	geo->setIndex( index );
	geo->setTypes( types );
	geo->setLengths( lens );
	endEditCP(geo);
		
    NodePtr node = Node::create();
	beginEditCP(node);
	node->setCore( geo );
	endEditCP(node);
	
	return node;
}


/*! \ingroup SimpleGeometry
	\return NodePtr the created cone
	\param height	the cone's height
	\param radius	the cone's radius
	\param sides	number of subdivisons in the x direction

makeCone creates a cone. It's base sits in the origin of the x/y plane. 
It's radius is \a radius and the base is subdivided into \a sides parts.
Vertically it is subdivided into 2 parts.

*/

NodePtr OSG::makeCone( Real32 height, Real32 radius, UInt16 sides )
{
	if ( height <= 0 || radius <= 0 || sides < 3 )
	{
		SWARNING << "makeCone: illegal parameters height=" << height 
				 << ", radius=" << radius 
				 << ", sides=" << sides 
				 << endl;
		return NullNode;
	}
	
	GeoPosition3fPtr		pnts  = GeoPosition3f::create();
	GeoNormal3fPtr		norms = GeoNormal3f::create();
	GeoIndexUI32Ptr		index = GeoIndexUI32::create();	
	GeoPLengthPtr		lens  = GeoPLength::create();	
	GeoPTypePtr			types = GeoPType::create();	
	
	UInt16 j;
	Real32 delta = 2.0 * Pi / sides;
	Real32 beta, x, y;

	// calc the vertices

	GeoPosition3f::FieldType * p = pnts->getFieldPtr();
	GeoNormal3f::FieldType   * n = norms->getFieldPtr();

	beginEditCP(pnts);
	beginEditCP(norms);
	
	p->addValue( Pnt3f(0,0,height) );
	n->addValue( Vec3f(0,0,1) );
	
	p->addValue( Pnt3f(0,0,0) );
	n->addValue( Vec3f(0,0,-1) );
		
	for ( j = 0; j < sides; j++ )
	{
		beta = j * delta;
		x = radius * cos(beta);
		y = radius * sin(beta);		
		
		p->addValue( Pnt3f(x, y, 0) );
		n->addValue( Vec3f(x, y, 0) );
	}
	
	for ( j = 0; j < sides; j++ )
	{
		beta = j * delta;
		x = (radius / 2.) * cos(beta);
		y = (radius / 2.) * sin(beta);
						
		p->addValue( Pnt3f(x, y, height / 2.) );
		n->addValue( Vec3f(x, y, height / 2.) );
	}

	endEditCP(pnts);
	endEditCP(norms);

	// create the faces
	
	GeoIndexUI32::FieldType * i = index->getFieldPtr();
	GeoPLength::FieldType   * l = lens->getFieldPtr();
	GeoPType::FieldType     * t = types->getFieldPtr();

	beginEditCP(index);
	beginEditCP(lens);
	beginEditCP(types);

	t->addValue(GL_TRIANGLE_FAN);
	l->addValue(sides+2);
	i->addValue(0);
	for ( j = 0; j < sides; j++ ) {
			i->addValue(j+2+sides);
	}
	i->addValue(2+sides); 
		
	t->addValue(GL_TRIANGLE_STRIP);
	l->addValue(sides*2+2);
	for ( j = 0; j < sides; j++ ) {
			i->addValue(j+2+sides);
			i->addValue(j+2);			
	}
	i->addValue(2+sides);
	i->addValue(2); 
		
	t->addValue(GL_TRIANGLE_FAN);
	l->addValue(sides+2);
	i->addValue(1);
	for ( j = 0; j < sides; j++ ) {
			i->addValue(j+2);
	}
	i->addValue(2);
	
	endEditCP(index);
	endEditCP(lens);
	endEditCP(types);

	// create the geometry
	
    GeometryPtr geo = Geometry::create();

 	beginEditCP(geo);
	geo->setPositions( pnts );
	geo->setNormals( norms );
	geo->setNormalPerVertex( true );
	geo->setIndex( index );
	geo->setTypes( types );
	geo->setLengths( lens );
	endEditCP(geo);
		
    NodePtr node = Node::create();
	beginEditCP(node);
	node->setCore( geo );
	endEditCP(node);
		
	return node;
}


/*! \ingroup SimpleGeometry
	\return NodePtr the created torus
	\param innerRadius	the torus' inner radius
	\param outerRadius	the torus' outer radius
	\param sides		number of subdivisons for the inner radius
	\param rings		number of subdivisons for the outer radius

makeTorus creates a torus in the x/y plane.

*/

NodePtr OSG::makeTorus( Real32 innerRadius, Real32 outerRadius, UInt16 sides, UInt16 rings )
{
	if ( innerRadius <= 0 || outerRadius <= 0 || sides < 3 || rings < 3 )
	{
		SWARNING << "makeTorus: illegal parameters innerRadius=" << innerRadius 
				 << ", outerRadius=" << outerRadius 
				 << ", sides=" << sides 
				 << ", rings=" << rings 
				 << endl;
		return NullNode;
	}
	
	GeoPosition3fPtr		pnts  = GeoPosition3f::create();
	GeoNormal3fPtr		norms = GeoNormal3f::create();
	GeoIndexUI32Ptr		index = GeoIndexUI32::create();	
	GeoPLengthPtr		lens  = GeoPLength::create();	
	GeoPTypePtr			types = GeoPType::create();	
	
	UInt16 a, b;
	Real32 theta, phi;
 	Real32 cosTheta, sinTheta;
  	Real32 ringDelta, sideDelta;

	// calc the vertices

	GeoPosition3f::FieldType * p = pnts->getFieldPtr();
	GeoNormal3f::FieldType   * n = norms->getFieldPtr();

	beginEditCP(pnts);
	beginEditCP(norms);
	
  	ringDelta = 2.0 * Pi / rings;
  	sideDelta = 2.0 * Pi / sides;

  	for (a = rings, theta = 0.0; a > 0; a--, theta += ringDelta) 
  	{
    		cosTheta = cos(theta);
    		sinTheta = sin(theta);
 		
    		for (b = sides, phi = 0; b > 0; b--, phi += sideDelta ) 
    		{
      			GLfloat cosPhi, sinPhi, dist;
 			
		     	cosPhi = cos(phi);
      			sinPhi = sin(phi);
      			dist = outerRadius + innerRadius * cosPhi;

      			n->addValue( Vec3f(cosTheta * cosPhi, -sinTheta * cosPhi, sinPhi) );
      			p->addValue( Pnt3f(cosTheta * dist, -sinTheta * dist, innerRadius * sinPhi) );
    		}
 	}	

	endEditCP(pnts);
	endEditCP(norms);

	// create the faces
	
	GeoIndexUI32::FieldType * i = index->getFieldPtr();
	GeoPLength::FieldType   * l = lens->getFieldPtr();
	GeoPType::FieldType     * t = types->getFieldPtr();

	beginEditCP(index);
	beginEditCP(lens);
	beginEditCP(types);

	for ( a = 0; a < sides; a++ ) 
	{
		t->addValue(GL_TRIANGLE_STRIP);
		l->addValue( ( rings + 1 ) * 2);
		
		for ( b = 0; b <= rings; b++ )
		{
			i->addValue( (b % rings) * sides + a );
			i->addValue( (b % rings) * sides + (a + 1) % sides );
		}
	}

	endEditCP(index);
	endEditCP(lens);
	endEditCP(types);

	// create the geometry
	
    GeometryPtr geo = Geometry::create();

 	beginEditCP(geo);
	geo->setPositions( pnts );
	geo->setNormals( norms );
	geo->setNormalPerVertex( true );
	geo->setIndex( index );
	geo->setTypes( types );
	geo->setLengths( lens );
	endEditCP(geo);
		
    NodePtr node = Node::create();
	beginEditCP(node);
	node->setCore( geo );
	endEditCP(node);
	
	return node;
}


/*! \ingroup SimpleGeometry
*/

Real32 setVecLen(Vec3f &vec, Real32 length ) 
{

	Real32 val1,val2,val3,len;

	vec.getValues( val1, val2, val3 );
	len = vec.length();
	if (len == 0.0) 
	{
		len = 1;
	} else 
	{
		len *= (1.0 / length);
	}
	vec.setValues( val1 / len, val2 / len, val3 / len);
	
	return vec.length();
}

/*! \ingroup SimpleGeometry
*/

static void subdivideTriangle( Vec3f &v1, 
						Vec3f &v2, 
						Vec3f &v3, 
						Int32 depth, 
						GeoPosition3f::FieldType *p, 
						GeoNormal3f::FieldType   *n,
						GeoIndexUI32::FieldType  *i,
						GeoPLength::FieldType    *l,
						GeoPType::FieldType      *t,
						Int32 *z, Real32 radius) {
			
	setVecLen( v1, radius );
	setVecLen( v2, radius );
	setVecLen( v3, radius );

	if (depth == 0) 
	{
		Vec3f norm;

		t->addValue( GL_TRIANGLES );
		l->addValue(3);
		
		norm = v1; norm.normalize();
		n->addValue( norm );
		p->addValue( v1 );
		i->addValue( (*z)++ );

		norm = v2; norm.normalize();
		n->addValue( norm );
		p->addValue( v2 );
		i->addValue( (*z)++ );

		norm = v3; norm.normalize();
		n->addValue( norm );
		p->addValue( v3 );
		i->addValue( (*z)++ );
					
		return;		
	}

	Vec3f v12, v23, v31;

	v12 = v1 + v2;
	v23 = v2 + v3;
	v31 = v3 + v1;
	
	v12 /= 2.0;
	v23 /= 2.0;
	v31 /= 2.0;
	
	subdivideTriangle(  v1, v12, v31, depth - 1, p,n,i,l,t, z, radius );
	subdivideTriangle(  v2, v23, v12, depth - 1, p,n,i,l,t, z, radius );
	subdivideTriangle(  v3, v31, v23, depth - 1, p,n,i,l,t, z, radius );
	subdivideTriangle( v12, v23, v31, depth - 1, p,n,i,l,t, z, radius );
		
}

/*! \ingroup SimpleGeometry
	\return NodePtr the created sphere
	\param depth	the sphere's subdivision depth
	\param radius	the sphere's radius

makeSphere creates a sphere centered in the origin. It is created by recursive 
subdivision of an icosahedron, with \a depth giving the number of subdivisions.

*/

NodePtr OSG::makeSphere( UInt16 depth, Real32 radius )
{	
	if ( depth < 1 || radius <= 0 )
	{
		SWARNING << "makeSphere: illegal parameters depth=" << depth 
				 << ", radius=" << radius 
				 << endl;
		return NullNode;
	}
	
	#define X .525731112119133606
	#define Z .850650808352039932	

	GeoPosition3fPtr		pnts  = GeoPosition3f::create();
	GeoNormal3fPtr		norms = GeoNormal3f::create();
	GeoIndexUI32Ptr		index = GeoIndexUI32::create();	
	GeoPLengthPtr		lens  = GeoPLength::create();	
	GeoPTypePtr			types = GeoPType::create();	
	Int32				j,z=0;
	
	Vec3f *v[12] = { new Vec3f( -X, 0.,  Z ),
					    new Vec3f(  X, 0.,  Z ),
			    		new Vec3f( -X, 0., -Z ),
					    new Vec3f(  X, 0., -Z ),
					    new Vec3f( 0.,  Z,  X ),
			    		new Vec3f( 0.,  Z, -X ),
					    new Vec3f( 0., -Z,  X ),
					    new Vec3f( 0., -Z, -X ),
			    		new Vec3f(  Z,  X, 0. ),
					    new Vec3f( -Z,  X, 0. ),
					    new Vec3f(  Z, -X, 0. ),
			    		new Vec3f( -Z, -X, 0. )   };
			    
	Int32 tr[20][3] = { {1,4,0},  {4,9,0},  {4,5,9},  {8,5,4},  {1,8,4},
					       {1,10,8}, {10,3,8}, {8,3,5},  {3,2,5},  {3,7,2},
					       {3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},
			    		   {10,1,6}, {11,0,9}, {2,11,9}, {5,2,9},  {11,2,7} };			      	
			    
	for ( j=0; j<12; j++ )
	{
		setVecLen( *v[j], radius );
	}
							
	GeoPosition3f::FieldType * p = pnts->getFieldPtr();
	GeoNormal3f::FieldType   * n = norms->getFieldPtr();
	GeoIndexUI32::FieldType * i = index->getFieldPtr();
	GeoPLength::FieldType   * l = lens->getFieldPtr();
	GeoPType::FieldType     * t = types->getFieldPtr();

	beginEditCP(pnts);
	beginEditCP(norms);
	beginEditCP(index);
	beginEditCP(lens);
	beginEditCP(types);
	
	for ( j=0; j<20; j++ ) 
	{
		subdivideTriangle( *v[ tr[j][0] ], *v[ tr[j][1] ], *v[ tr[j][2] ],
				   depth, p, n, i, l, t, &z, radius );
	}
				   					
	endEditCP(pnts);
	endEditCP(norms);
	endEditCP(index);
	endEditCP(lens);
	endEditCP(types);
	
	// create the geometry
	
    GeometryPtr geo = Geometry::create();

 	beginEditCP(geo);
	geo->setPositions( pnts );
	geo->setNormals( norms );
	geo->setNormalPerVertex( true );
	geo->setIndex( index );
	geo->setTypes( types );
	geo->setLengths( lens );
	endEditCP(geo);
		
    NodePtr node = Node::create();
	beginEditCP(node);
	node->setCore( geo );
	endEditCP(node);	
		
	return node;
}



///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

