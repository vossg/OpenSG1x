#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <GL/glut.h>

#include <OSGBaseFunctions.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include "OSGGeometry.h"
#include "OSGSimpleGeometry.h"

#include "OSGPrimitiveIterator.h"
#include "OSGTriangleIterator.h"
#include "OSGFaceIterator.h"

OSG_USING_NAMESPACE


int main (int argc, char **argv)
{
    osgInit(argc, argv);

	NodePtr n;
	GeometryPtr g;
	
	// OSG
	
	// create the test geometry
    n = Node::create();
    g = Geometry::create();
	n->setCore( g );

	GeoPosition3f::PtrType pnts = GeoPosition3f::create();
	g->setPositions( pnts );

	MFPnt3f* p = pnts->getFieldPtr();

	osgBeginEditCP(pnts);
	p->addValue( Pnt3f( -1, -1, -1) );
	p->addValue( Pnt3f(  1, -1, -1) );
	p->addValue( Pnt3f(  1,  1, -1) );
	p->addValue( Pnt3f( -1,  1, -1) );
	p->addValue( Pnt3f( -1, -1,  1) );
	p->addValue( Pnt3f(  1, -1,  1) );
	p->addValue( Pnt3f(  1,  1,  1) );
	p->addValue( Pnt3f( -1,  1,  1) );
	osgEndEditCP(pnts);


	GeoColor4ub::PtrType cols = GeoColor4ub::create();
	g->setColors( cols );
	g->setColorPerVertex( true );
	osgBeginEditCP(cols);
	cols->getFieldPtr()->addValue( Color4ub( 255, 255, 255, 255) );
	cols->getFieldPtr()->addValue( Color4ub( 255, 255, 255, 255) );
	cols->getFieldPtr()->addValue( Color4ub(   0, 255, 255, 255) );
	cols->getFieldPtr()->addValue( Color4ub(   0, 255, 255, 255) );
	cols->getFieldPtr()->addValue( Color4ub( 255,   0, 255, 255) );
	cols->getFieldPtr()->addValue( Color4ub( 255, 255,   0, 255) );
	cols->getFieldPtr()->addValue( Color4ub( 255,   0,   0, 255) );
	cols->getFieldPtr()->addValue( Color4ub(   0, 255,   0, 255) );
	osgEndEditCP(cols);

	// don't use normals to test non-existing attributes

	// Make me one with everything...

	GeoPTypePtr type = GeoPType::create();	
	g->setTypes( type );
	osgBeginEditCP(type);
	type->getFieldPtr()->addValue( GL_POINTS );
	type->getFieldPtr()->addValue( GL_LINES );
	type->getFieldPtr()->addValue( GL_LINE_LOOP );
	type->getFieldPtr()->addValue( GL_LINE_STRIP );
	type->getFieldPtr()->addValue( GL_TRIANGLES );
	type->getFieldPtr()->addValue( GL_TRIANGLE_STRIP );
	type->getFieldPtr()->addValue( GL_TRIANGLE_FAN );
	type->getFieldPtr()->addValue( GL_QUADS );
	type->getFieldPtr()->addValue( GL_QUAD_STRIP );
	type->getFieldPtr()->addValue( GL_POLYGON );
	type->getFieldPtr()->addValue( GL_POLYGON );
	type->getFieldPtr()->addValue( GL_POLYGON );
	osgEndEditCP(type);


	GeoPLengthPtr lens = GeoPLength::create();	
	g->setLengths( lens );
	osgBeginEditCP(lens);
	{
	static Int32 l[] = { 2,4,3,3,9,5,5,12,6,3,4,5,-1};
	for ( int ind = 0; l[ind] >= 0; ind++ )
		lens->getFieldPtr()->addValue( l[ind] );
	}
	osgEndEditCP(lens);

	
	GeoIndexUI32Ptr index = GeoIndexUI32::create();	
	g->setIndex( index );
	osgBeginEditCP(index);
	{
	static Int32 i[] = { 0,1, 0,1,1,2, 4,5,6, 5,6,7, 0,1,2,1,2,3,2,3,4,
						  3,0,2,1,6, 0,3,2,1,5, 0,1,2,3,4,5,6,7,0,1,4,5,
						  6,5,7,4,3,0, 0,1,2, 0,1,2,3, 0,1,2,3,4, -1};
	for ( int ind = 0; i[ind] >= 0; ind++ )
		index->getFieldPtr()->addValue( i[ind] );
	}
	osgEndEditCP(index);

	
	cerr << g->getLengths()->getSize() << " primitives with ";
	for ( int j = 0; j < g->getLengths()->getSize(); j++ )
	{
		cerr <<  g->getLengths()->getValue( j ) << " ";
	}
	cerr << " points" << endl << g->getIndex()->getSize() << " indices: ";
	for ( int j = 0; j < g->getIndex()->getSize(); j++ )
	{
		cerr <<  g->getIndex()->getValue( j ) << " ";
	}
	
	// Try the primitive iterator
	cerr << endl << endl << "Primitive Iterator:" << endl;
	
	PrimitiveIterator pi;
	
	for ( pi = g->beginPrimitives(); pi != g->endPrimitives(); ++pi )
	{
		cerr << "Primitive " << pi.getPrimIndex() << ": "
		 	 << Geometry::mapType( pi.getPrimType() ) << " with " 
			 << pi.getPrimLength() << " points" << endl;
		for ( int j = 0; j < pi.getPrimLength(); j++ )
		{
			cerr << "Point " << j << ":  " << pi.getPositionIndex( j ) << ": "
				 << pi.getPosition( j );
			cerr << "\tcol: " << pi.getColorIndex( j );
			cerr << "\tnorm: " << pi.getNormalIndex( j ) << endl;
		}
	}
	
	cerr << endl << "Triangle Iterator:" << endl;
	
	// Try the triangle iterator
	TriangleIterator i;
	
	for ( i = g->beginTriangles(); i != g->endTriangles(); ++i )
	{
		cerr << "Triangle " << i.getTriIndex() << endl;
		cerr << "Points:  " << i.getPositionIndex( 0 ) << ": "
						   << i.getPosition( 0 ) << ", "
						   << i.getPositionIndex( 1 ) << ": "
						   << i.getPosition( 1 ) << ", "
						   << i.getPositionIndex( 2 ) << ": "
						   << i.getPosition( 2 ) << endl;
		cerr << "Colors:  " << i.getColorIndex( 0 ) << ","
						   << i.getColorIndex( 1 ) << ","
						   << i.getColorIndex( 2 ) << endl;
		cerr << "Normals: " << i.getNormalIndex( 0 ) << ","
						   << i.getNormalIndex( 1 ) << ","
						   << i.getNormalIndex( 2 ) << endl;
	}
	
	cerr << endl << "Face Iterator:" << endl;
	
	// Try the Face iterator
	FaceIterator fi;
	
	for ( fi = g->beginFaces(); fi != g->endFaces(); ++fi )
	{
		cerr << "Face " << fi.getFaceIndex() << endl;
		cerr << "Points:  " << fi.getPositionIndex( 0 ) << ": "
						   << fi.getPosition( 0 ) << ", "
						   << fi.getPositionIndex( 1 ) << ": "
						   << fi.getPosition( 1 ) << ", "
						   << fi.getPositionIndex( 2 ) << ": "
						   << fi.getPosition( 2 )  << ", "
						   << fi.getPositionIndex( 3 ) << ": "
						   << fi.getPosition( 3 ) << endl;
		cerr << "Colors:  " << fi.getColorIndex( 0 ) << ","
						   << fi.getColorIndex( 1 ) << ","
						   << fi.getColorIndex( 2 ) << ","
						   << fi.getColorIndex( 3 ) << endl;
		cerr << "Normals: " << fi.getNormalIndex( 0 ) << ","
						   << fi.getNormalIndex( 1 ) << ","
						   << fi.getNormalIndex( 2 ) << ","
						   << fi.getNormalIndex( 3 ) << endl;
	}
	
	// try a second time, to see if restart works
	
	cerr << endl << "Triangle Iterator (second run):" << endl;
	
	for ( i = g->beginTriangles(); i != g->endTriangles(); ++i )
	{
		cerr << "Triangle " << i.getTriIndex() << endl;
		cerr << "Points:  " << i.getPositionIndex( 0 ) << ": "
						   << i.getPosition( 0 ) << ", "
						   << i.getPositionIndex( 1 ) << ": "
						   << i.getPosition( 1 ) << ", "
						   << i.getPositionIndex( 2 ) << ": "
						   << i.getPosition( 2 ) << endl;
		cerr << "Colors:  " << i.getColorIndex( 0 ) << ","
						   << i.getColorIndex( 1 ) << ","
						   << i.getColorIndex( 2 ) << endl;
		cerr << "Normals: " << i.getNormalIndex( 0 ) << ","
						   << i.getNormalIndex( 1 ) << ","
						   << i.getNormalIndex( 2 ) << endl;
	}
	
    return 0;
}

