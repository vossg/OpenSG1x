#include <OSGConfig.h>

#include <iostream>

#include <OSGGLUT.h>

#include <OSGFieldContainerFactory.h>
#include <OSGBaseFunctions.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGMatrix.h>
#include <OSGQuaternion.h>
#include "OSGGeometry.h"
#include <OSGGeoProperty.h>

/*
#include "OSGGeoPropPositions.h"
#include "OSGGeoPropIndices.h"
#include "OSGGeoPropColors.h"
#include "OSGGeoPropPtrs.h"
*/

using namespace OSG;

DrawAction * dact;

NodePtr  root;

Matrix accumM;
Matrix stepM;


void 
display(void)
{
    static float a = 0;

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();
    glRotatef( a, 0,1,0 );
//    glMultMatrixf(accumM.getValues());
    dact->apply( root );

    glPopMatrix();

    a+=1;

    accumM.mult(stepM);

    glutSwapBuffers();
}

int main (int argc, char **argv)
{
    // GLUT init

    osgInit(argc, argv);
    
    FieldContainerPtr pProto = Geometry::getClassType().getPrototype();

    GeometryPtr pGeoProto = GeometryPtr::dcast(pProto);

    if(pGeoProto != NullFC)
    {
        pGeoProto->setDlistCache(false);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("OpenSG");
    // glutKeyboardFunc(key);
    // glutReshapeFunc(resize);
    glutDisplayFunc(display);       
    // glutMouseFunc(mouse);   
    // glutMotionFunc(motion); 
    
    glutIdleFunc(display);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60, 1, 0.1, 10 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( 3, 3, 3,  0, 0, 0,   0, 1, 0 );
    
    glEnable( GL_DEPTH_TEST );
    // glEnable( GL_LIGHTING );

    // OSG

    Quaternion stepQ;

    stepQ.setValueAsAxisDeg(0., 1., 0., 1.);

    stepM.setRotate(stepQ);

    root = Node::create();
    GeometryPtr g1 = Geometry::create();

        beginEditCP(root);
    root->setCore( g1 );
        endEditCP(root);

        beginEditCP(g1);
    cerr << "Geometry Node: " << hex << (Geometry*) g1.getCPtr() << endl;

    GeoPositions3fPtr pnts = GeoPositions3f::create();
    g1->setPositions( pnts );
    cerr << "Points property: " << hex << pnts << endl;

    cerr << "Geometry Points: " << hex << g1->getPositions() << endl;


    MFPnt3f* p = pnts->getFieldPtr();

    beginEditCP(pnts);
    p->push_back( Pnt3f( -1, -1, -1) );
    p->push_back( Pnt3f(  1, -1, -1) );
    p->push_back( Pnt3f(  1,  1, -1) );
    p->push_back( Pnt3f( -1,  1, -1) );
    p->push_back( Pnt3f( -1, -1,  1) );
    p->push_back( Pnt3f(  1, -1,  1) );
    p->push_back( Pnt3f(  1,  1,  1) );
    p->push_back( Pnt3f( -1,  1,  1) );
    endEditCP(pnts);


    GeoColors4ubPtr cols = GeoColors4ub::create();
    g1->setColors( cols );
    beginEditCP(cols);
    cols->getFieldPtr()->push_back( Color4ub( 255, 255, 255, 255) );
    cols->getFieldPtr()->push_back( Color4ub(   0, 255, 255, 255) );
    cols->getFieldPtr()->push_back( Color4ub( 255,   0, 255, 255) );
    cols->getFieldPtr()->push_back( Color4ub( 255, 255,   0, 255) );
    cols->getFieldPtr()->push_back( Color4ub( 255,   0,   0, 255) );
    cols->getFieldPtr()->push_back( Color4ub(   0, 255,   0, 255) );
    endEditCP(cols);


    // Note: the object has texCoords, but no texture, so don't be suprised to 
    // not see the texture. ;)
    GeoTexCoords2fPtr texs = GeoTexCoords2f::create();
    g1->setTexCoords( texs );
    beginEditCP(texs);
    texs->push_back( Vec2f( 0, 0 ) );
    texs->push_back( Vec2f( 1, 0 ) );
    texs->push_back( Vec2f( 1, 1 ) );
    texs->push_back( Vec2f( 0, 1 ) );
    texs->push_back( Vec2f( 0, 0 ) );
    texs->push_back( Vec2f( 2, 0 ) );
    texs->push_back( Vec2f( 2, 2 ) );
    texs->push_back( Vec2f( 0, 2 ) );
    endEditCP(texs);

    // use second texture coordinates
    texs = GeoTexCoords2f::create();
    g1->setTexCoords1( texs );
    beginEditCP(texs);
    texs->push_back( Vec2f( 0, 0 ) );
    texs->push_back( Vec2f( 1, 0 ) );
    texs->push_back( Vec2f( 1, 1 ) );
    texs->push_back( Vec2f( 0, 1 ) );
    texs->push_back( Vec2f( 0, 0 ) );
    texs->push_back( Vec2f( 2, 0 ) );
    texs->push_back( Vec2f( 2, 2 ) );
    texs->push_back( Vec2f( 0, 2 ) );
    endEditCP(texs);
    
    GeoTexCoords3fPtr texs3 = GeoTexCoords3f::create();
    g1->setTexCoords( texs3 );
    beginEditCP(texs3);
    texs3->getField().push_back( Vec3f( 0, 0, 0 ) );
    texs3->getField().push_back( Vec3f( 1, 0, 0 ) );
    texs3->getField().push_back( Vec3f( 1, 1, 0 ) );
    texs3->getField().push_back( Vec3f( 0, 1, 0 ) );
    texs3->getField().push_back( Vec3f( 0, 0, 0 ) );
    texs3->getField().push_back( Vec3f( 3, 0, 0 ) );
    texs3->getField().push_back( Vec3f( 3, 3, 0 ) );
    texs3->getField().push_back( Vec3f( 0, 3, 0 ) );
    endEditCP(texs3);

    GeoIndicesUI32Ptr index = GeoIndicesUI32::create();     
    g1->setIndices( index );
    beginEditCP(index);
    index->getFieldPtr()->push_back( 0 ); // PNT index
//  index->getFieldPtr()->push_back( 0 ); // C index
    index->getFieldPtr()->push_back( 1 ); // PNT index
//  index->getFieldPtr()->push_back( 0 ); // C index
    index->getFieldPtr()->push_back( 2 ); // PNT index
//  index->getFieldPtr()->push_back( 1 ); // C index
    index->getFieldPtr()->push_back( 3 ); // PNT index
//  index->getFieldPtr()->push_back( 1 ); // C index
    index->getFieldPtr()->push_back( 4 ); // PNT index
//  index->getFieldPtr()->push_back( 2 ); // C index
    index->getFieldPtr()->push_back( 5 ); // PNT index
//  index->getFieldPtr()->push_back( 3 ); // C index
    index->getFieldPtr()->push_back( 6 ); // PNT index
//  index->getFieldPtr()->push_back( 4 ); // C index
    index->getFieldPtr()->push_back( 7 ); // PNT index
//  index->getFieldPtr()->push_back( 5 ); // C index
    endEditCP(index);

//    g1->getIndexMapping().push_back( 
//      Geometry::MapPosition | Geometry::MapNormal |
//      Geometry::MapTexCoords );
//    g1->getIndexMapping().push_back( Geometry::MapColor );


    GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    g1->setLengths( lens );
    beginEditCP(lens);
    lens->push_back( 4 );
    lens->push_back( 4 );
    endEditCP(lens);


    GeoPTypesPtr type = GeoPTypesUI8::create();     
    g1->setTypes( type );
    beginEditCP(type);
    type->push_back( GL_POLYGON );
    type->push_back( GL_POLYGON );
    endEditCP(type);

        endEditCP(g1);
    
    cerr << "Geometry type " << g1->getType().getId() << endl;
    
    dact = DrawAction::create();
    
    glutMainLoop();

    
    return 0;
}

