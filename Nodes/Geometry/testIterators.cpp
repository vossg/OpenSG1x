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
    
    int j;
    
    // OSG
    
    // create the test geometry
    n = Node::create();
    g = Geometry::create();
    n->setCore( g );

    GeoPositions3f::PtrType pnts = GeoPositions3f::create();
    g->setPositions( pnts );

    MFPnt3f* p = pnts->getFieldPtr();

    beginEditCP(pnts);
    p->addValue( Pnt3f( -1, -1, -1) );
    p->addValue( Pnt3f(  1, -1, -1) );
    p->addValue( Pnt3f(  1,  1, -1) );
    p->addValue( Pnt3f( -1,  1, -1) );
    p->addValue( Pnt3f( -1, -1,  1) );
    p->addValue( Pnt3f(  1, -1,  1) );
    p->addValue( Pnt3f(  1,  1,  1) );
    p->addValue( Pnt3f( -1,  1,  1) );
    endEditCP(pnts);


    GeoColors4ub::PtrType cols = GeoColors4ub::create();
    g->setColors( cols );
    g->getIndexMapping().addValue( Geometry::MapPosition | 
                                   Geometry::MapColor );
    
    beginEditCP(cols);
    cols->getFieldPtr()->addValue( Color4ub( 255, 255, 255, 255) );
    cols->getFieldPtr()->addValue( Color4ub( 255, 255, 255, 255) );
    cols->getFieldPtr()->addValue( Color4ub(   0, 255, 255, 255) );
    cols->getFieldPtr()->addValue( Color4ub(   0, 255, 255, 255) );
    cols->getFieldPtr()->addValue( Color4ub( 255,   0, 255, 255) );
    cols->getFieldPtr()->addValue( Color4ub( 255, 255,   0, 255) );
    cols->getFieldPtr()->addValue( Color4ub( 255,   0,   0, 255) );
    cols->getFieldPtr()->addValue( Color4ub(   0, 255,   0, 255) );
    endEditCP(cols);

    // don't use normals to test non-existing attributes

    // Make me one with everything...

    GeoPTypesUI8Ptr type = GeoPTypesUI8::create();  
    g->setTypes( type );
    beginEditCP(type);
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
    endEditCP(type);


    GeoPLengthsUI32Ptr lens = GeoPLengthsUI32::create();    
    g->setLengths( lens );
    beginEditCP(lens);
    {
    static Int32 l[] = { 2,4,3,3,9,5,5,12,6,3,4,5,-1};
    for ( int ind = 0; l[ind] >= 0; ind++ )
        lens->getFieldPtr()->addValue( l[ind] );
    }
    endEditCP(lens);

    
    GeoIndicesUI32Ptr index = GeoIndicesUI32::create();     
    g->setIndices( index );
    beginEditCP(index);
    {
    static Int32 i[] = { 0,1, 0,1,1,2, 4,5,6, 5,6,7, 0,1,2,1,2,3,2,3,4,
                          3,0,2,1,6, 0,3,2,1,5, 0,1,2,3,4,5,6,7,0,1,4,5,
                          6,5,7,4,3,0, 0,1,2, 0,1,2,3, 0,1,2,3,4, -1};
    for ( int ind = 0; i[ind] >= 0; ind++ )
        index->getFieldPtr()->addValue( i[ind] );
    }
    endEditCP(index);

    
    cerr << g->getLengths()->getSize() << " primitives with ";
    for ( j = 0; j < g->getLengths()->getSize(); j++ )
    {
        cerr <<  g->getLengths()->getValue( j ) << " ";
    }
    cerr << " points" << endl << g->getIndices()->getSize() << " indices: ";
    for ( j = 0; j < g->getIndices()->getSize(); j++ )
    {
        cerr <<  g->getIndices()->getValue( j ) << " ";
    }
    
    // Try the primitive iterator
    cerr << endl << endl << "Primitive Iterator:" << endl;
    
    PrimitiveIterator pi;
    
    for ( pi = g->beginPrimitives(); pi != g->endPrimitives(); ++pi )
    {
        cerr << "Primitive " << pi.getIndex() << ": "
             << Geometry::mapType( pi.getType() ) << " with " 
             << pi.getLength() << " points" << endl;
        for ( j = 0; j < pi.getLength(); j++ )
        {
            cerr << "Point " << j << ":  " << pi.getPositionIndex( j ) << ": "
                 << pi.getPosition( j );
            cerr << "\tcol: " << pi.getColorIndex( j );
            cerr << "\tnorm: " << pi.getNormalIndex( j ) << endl;
        }
    }
    
    // try seek
    
    cerr << "Checking seek...";
    
    PrimitiveIterator pi2(g);
    
    for ( pi = g->beginPrimitives(), j = 0; 
            pi != g->endPrimitives(); ++pi,++j )
    {
        pi2.seek( j );
        
        if ( pi.getIndex()  != pi2.getIndex() ||
             pi.getType()   != pi2.getType() || 
             pi.getLength() != pi2.getLength()
            )
        {
            cerr << "Seek mismatch!" << endl;
            cerr << "Primitive " << pi.getIndex() << ": "
                 << Geometry::mapType( pi.getType() ) << " with " 
                 << pi.getLength() << " points" << endl;
            cerr << "Primitive " << pi2.getIndex() << ": "
                 << Geometry::mapType( pi2.getType() ) << " with " 
                 << pi2.getLength() << " points" << endl;
        }
        for ( int k = 0; k < pi.getLength(); k++ )
        {
            if ( pi.getPositionIndex( k )   != pi2.getPositionIndex( k ) ||
                 pi.getColorIndex( k )      != pi2.getColorIndex( k ) ||
                 pi.getNormalIndex( k )     != pi2.getNormalIndex( k ) )
            {            
                cerr << "Prim " << j << endl;
                cerr << "Point " << k << ":  " << pi.getPositionIndex( k );
                cerr << "\tcol: " << pi.getColorIndex( k );
                cerr << "\tnorm: " << pi.getNormalIndex( k ) << endl;
                cerr << "Point " << k << ":  " << pi2.getPositionIndex( k );
                cerr << "\tcol: " << pi2.getColorIndex( k );
                cerr << "\tnorm: " << pi2.getNormalIndex( k ) << endl;
            }
        }
    }
    cerr << "done" << endl;
    
    
    // Try the triangle iterator
    
    cerr << endl << "Triangle Iterator:" << endl;
    
    TriangleIterator ti;
    
    for ( ti = g->beginTriangles(); ti != g->endTriangles(); ++ti )
    {
        cerr << "Triangle " << ti.getIndex() << endl;
        cerr << "Points:  " << ti.getPositionIndex( 0 ) << ": "
                           << ti.getPosition( 0 ) << ", "
                           << ti.getPositionIndex( 1 ) << ": "
                           << ti.getPosition( 1 ) << ", "
                           << ti.getPositionIndex( 2 ) << ": "
                           << ti.getPosition( 2 ) << endl;
        cerr << "Colors:  " << ti.getColorIndex( 0 ) << ","
                           << ti.getColorIndex( 1 ) << ","
                           << ti.getColorIndex( 2 ) << endl;
        cerr << "Normals: " << ti.getNormalIndex( 0 ) << ","
                           << ti.getNormalIndex( 1 ) << ","
                           << ti.getNormalIndex( 2 ) << endl;
    }
    
    cerr << "Checking seek...";
    
    TriangleIterator ti2(g);
    
    for ( ti = g->beginTriangles(), j = 0; 
            ti != g->endTriangles(); ++ti,++j )
    {
        ti2.seek( j );
        
        if ( ti.getIndex()  != ti2.getIndex() )
        {
            cerr << "Seek mismatch!" << endl;
            cerr << "Primitive " << ti.getIndex() << endl;
            cerr << "Primitive " << ti2.getIndex() << endl;
        }
        for ( int k = 0; k < 3; k++ )
        {
            if ( ti.getPositionIndex( k )   != ti2.getPositionIndex( k ) ||
                 ti.getColorIndex( k )      != ti2.getColorIndex( k ) ||
                 ti.getNormalIndex( k )     != ti2.getNormalIndex( k ) )
            {            
                cerr << "Prim " << j << endl;
                cerr << "Point " << k << ":  " << ti.getPositionIndex( k );
                cerr << "\tcol: " << ti.getColorIndex( k );
                cerr << "\tnorm: " << ti.getNormalIndex( k ) << endl;
                cerr << "Point " << k << ":  " << ti2.getPositionIndex( k );
                cerr << "\tcol: " << ti2.getColorIndex( k );
                cerr << "\tnorm: " << ti2.getNormalIndex( k ) << endl;
            }
        }
    
    }
    
    cerr << "done" << endl;
    
    
    
    cerr << endl << "Face Iterator:" << endl;
    
    // Try the Face iterator
    FaceIterator fi;
    
    for ( fi = g->beginFaces(); fi != g->endFaces(); ++fi )
    {
        cerr << "Face " << fi.getIndex() << endl;
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
    
    // try seek
    
    cerr << "Checking seek...";
    
    FaceIterator fi2(g);
    
    for ( fi = g->beginFaces(), j = 0; 
            fi != g->endFaces(); ++fi,++j )
    {
        fi2.seek( j );
        
        if ( fi.getIndex()  != fi2.getIndex() )
        {
            cerr << "Seek mismatch!" << endl;
            cerr << "Primitive " << fi.getIndex() << endl;
            cerr << "Primitive " << fi2.getIndex() << endl;
        }
        for ( int k = 0; k < 4; k++ )
        {
            if ( fi.getPositionIndex( k )   != fi2.getPositionIndex( k ) ||
                 fi.getColorIndex( k )      != fi2.getColorIndex( k ) ||
                 fi.getNormalIndex( k )     != fi2.getNormalIndex( k ) )
            {            
                cerr << "Prim " << j << endl;
                cerr << "Point " << k << ":  " << fi.getPositionIndex( k );
                cerr << "\tcol: " << fi.getColorIndex( k );
                cerr << "\tnorm: " << fi.getNormalIndex( k ) << endl;
                cerr << "Point " << k << ":  " << fi2.getPositionIndex( k );
                cerr << "\tcol: " << fi2.getColorIndex( k );
                cerr << "\tnorm: " << fi2.getNormalIndex( k ) << endl;
            }
        }
    }
    cerr << "done" << endl;
    
    
    // try a second time, to see if restart works
    
    cerr << endl << "Triangle Iterator (second run):" << endl;
    
    for ( ti = g->beginTriangles(); ti != g->endTriangles(); ++ti )
    {
        cerr << "Triangle " << ti.getIndex() << endl;
        cerr << "Points:  " << ti.getPositionIndex( 0 ) << ": "
                           << ti.getPosition( 0 ) << ", "
                           << ti.getPositionIndex( 1 ) << ": "
                           << ti.getPosition( 1 ) << ", "
                           << ti.getPositionIndex( 2 ) << ": "
                           << ti.getPosition( 2 ) << endl;
        cerr << "Colors:  " << ti.getColorIndex( 0 ) << ","
                           << ti.getColorIndex( 1 ) << ","
                           << ti.getColorIndex( 2 ) << endl;
        cerr << "Normals: " << ti.getNormalIndex( 0 ) << ","
                           << ti.getNormalIndex( 1 ) << ","
                           << ti.getNormalIndex( 2 ) << endl;
    }
    
    return 0;
}

