#include <OSGConfig.h>

#include <iostream>

#include <OSGGLUT.h>

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGLine.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>
#include <OSGSimpleMaterial.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGFieldContainerPtr.h>

#include <OSGTriangleIterator.h>

#include "OSGIntersectAction.h"

using namespace OSG;

DrawAction * dact;

NodePtr  root;
NodePtr  iroot;
GeoPositions3fPtr points;

void 
display(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();
    glRotatef( glutGet( GLUT_ELAPSED_TIME ) / 50.f, 0,0,1 );
    dact->apply( root );

    glPopMatrix();

    glutSwapBuffers();
}


// test functions
// !!!these are to be moved into the respective nodes once this works!!!


// Group: traverse all children

Action::ResultE groupEnter(CNodePtr&, Action *) 
{ 
    return Action::Continue; 
}

// Geometry: test all triangles

Action::ResultE geometryEnter(CNodePtr& node, Action * action) 
{ 
    IntersectAction * ia = dynamic_cast<IntersectAction*>(action);
    NodePtr n( node );
    Geometry* core =  dynamic_cast<Geometry*>(n->getCore().getCPtr());

    TriangleIterator it;
    Real32 t;
    Vec3f norm;
    
    for ( it = core->beginTriangles(); it != core->endTriangles(); ++it )
    {
        if ( ia->getLine().intersect(   it.getPosition(0), 
                                        it.getPosition(1),
                                        it.getPosition(2), t, &norm ) )
        {
           ia->setHit( t, NodePtr(node), it.getIndex(), norm );
        }
    }
    
    return Action::Continue; 
}

// Transform: transform the ray and test all children

Action::ResultE transformEnter(CNodePtr& node, Action * action) 
{ 
    IntersectAction * ia = dynamic_cast<IntersectAction*>(action);
    NodePtr n( node );
    Transform* core =  dynamic_cast<Transform*>(n->getCore().getCPtr());
    Matrix m = core->getMatrix();
    m.invert();
    
    Pnt3f pos;
    Vec3f dir;
    m.multFullMatrixPnt( ia->getLine().getPosition(), pos );
    m.multMatrixVec( ia->getLine().getDirection(), dir );
    
    ia->setLine( Line( pos, dir ), ia->getMaxDist() );
    return Action::Continue; 
}

Action::ResultE transformLeave(CNodePtr& node, Action * action) 
{ 
    IntersectAction * ia = dynamic_cast<IntersectAction*>(action);
    NodePtr n( node );
    Transform* core =  dynamic_cast<Transform*>(n->getCore().getCPtr());
    Matrix &m = core->getMatrix();
    
    Pnt3f pos;
    Vec3f dir;
    m.multFullMatrixPnt( ia->getLine().getPosition(), pos );
    m.multMatrixVec( ia->getLine().getDirection(), dir );
    
    ia->setLine( Line( pos, dir ), ia->getMaxDist() );
    return Action::Continue; 
}


void key( unsigned char key, int , int )
{
    switch ( key )
    {
    case 27:    exit(0);
    }
    
    // Intersect
    
    IntersectAction * act = IntersectAction::create();
    
    static Pnt3f pnts[] = { Pnt3f( 0,0,1 ), Pnt3f( 1,0,1),  Pnt3f( 2,0,1), 
                Pnt3f( 3,0,1), Pnt3f( 0,0,1 ), Pnt3f( 0,0,1 ), 
                Pnt3f( 0,0,1 ),Pnt3f( 0,0,1 ), Pnt3f( 0.9,0.9,1 ), 
                Pnt3f(-Inf,-Inf,-Inf) };
    static Vec3f dirs[] = { Vec3f( 0,0,-1), Vec3f( 0,0,-1), Vec3f( 0,0,-1),  
                Vec3f( 0,0,-1), Vec3f( 0,-.2,-1), Vec3f( 0,.2,-1),  
                Vec3f( -.2,-.2,-1), Vec3f( .2,.2,-1), Vec3f( 0,0,-1 ),
                Vec3f(-Inf,-Inf,-Inf) };
    
    static int i = 0;

    act->setLine( Line( pnts[i], dirs[i]) );

    act->apply( iroot );

    std::cerr << "Line " << act->getLine().getPosition() << " dir " 
         << act->getLine().getDirection() << " hit: " << act->didHit() << " ";

    beginEditCP(points);
    points->setValue( pnts[i], 0 );
    points->setValue( pnts[i] + (dirs[i])*(Real32)(3.0), 1 );

    if ( act->didHit() )
    {
        std::cerr << " object " << act->getHitObject() 
             << " tri " << act->getHitTriangle() 
             << " at " << act->getHitPoint();

        TriangleIterator it( act->getHitObject() );
        it.seek( act->getHitTriangle() );
        
        Matrix m;
        act->getHitObject()->getToWorld(m);

        Pnt3f p = it.getPosition(0);
        m.multMatrixPnt( p );
        points->setValue( p, 2 );
        p = it.getPosition(1);
        m.multMatrixPnt( p );
        points->setValue( p, 3 );
        p = it.getPosition(2);
        m.multMatrixPnt( p );
        points->setValue( p, 4 );
    }
    else
    {
        points->setValue( Pnt3f(0,0,0), 2 );
        points->setValue( Pnt3f(0,0,0), 3 );
        points->setValue( Pnt3f(0,0,0), 4 );
    }
    endEditCP(points);

    std::cerr << std::endl;

    glutPostRedisplay();
    
    if ( pnts[++i][0] == -Inf )
        i = 0;
}


int main (int argc, char **argv)
{
    osgInit(argc, argv);

    FieldContainerPtr pProto = Geometry::getClassType().getPrototype();

    GeometryPtr pGeoProto = GeometryPtr::dcast(pProto);

    if(pGeoProto != NullFC)
    {
        pGeoProto->setDlistCache(false);
    }

    // init GLUT
    
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("OpenSG");
    glutKeyboardFunc(key);
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
    gluLookAt( 3, 3, 3,  0, 0, 0,   0, 0, 1 );
    
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glLineWidth( 3 );

#if 0   
    // for testing only: register Node type functions

    IntersectAction::registerEnterDefault(Group::getStaticType(), 
                               osgFunctionFunctor2(groupEnter));
    IntersectAction::registerEnterDefault(Geometry::getStaticType(), 
                               osgFunctionFunctor2(geometryEnter));
    IntersectAction::registerEnterDefault(Transform::getStaticType(), 
                               osgFunctionFunctor2(transformEnter));
    IntersectAction::registerLeaveDefault(Transform::getStaticType(), 
                               osgFunctionFunctor2(transformLeave));
#endif
    
    // create test scene
  
    SimpleMaterialPtr white = SimpleMaterial::create();
    SimpleMaterialPtr red = SimpleMaterial::create();
    
    white->setEmission( Color3f( 1,1,1 ) );
    red->setEmission( Color3f( 1,0,0 ) );
    
    //  g1->(g2->g3->p1,t1->p2)
    GeometryPtr g;
    NodePtr  p1 = makePlane( 2,2,2,2 );
    g = GeometryPtr::dcast(p1->getCore());
    g->setMaterial( white );
    p1->updateVolume();
    NodePtr  p2 = makePlane( 2,2,2,2 );
    g = GeometryPtr::dcast(p2->getCore());
    g->setMaterial( white );
    p2->updateVolume();
    
    NodePtr g4 = Node::create();
    TransformPtr t1 = Transform::create();
    beginEditCP(t1);
    t1->getMatrix().setRotate( Quaternion( Vec3f(1,0,0), 30 ) );
    endEditCP(t1);
    beginEditCP(g4);
    g4->setCore( t1 );
    g4->addChild( p2 );
    g4->updateVolume();
    endEditCP(g4);

    NodePtr g3 = Node::create();
    GroupPtr g3c = Group::create();
    beginEditCP(g3);
    g3->setCore( g3c );
    g3->addChild( p1 );
    g3->updateVolume();
    endEditCP(g3);
    
    NodePtr g2 = Node::create();
    GroupPtr g2c = Group::create();
    beginEditCP(g2);
    g2->setCore( g2c );
    g2->addChild( g3 );
    g2->updateVolume();
    endEditCP(g2);

    iroot = Node::create();
    GroupPtr g1c = Group::create();
    beginEditCP(iroot);
    iroot->setCore( g1c );
    iroot->addChild( g2 );
    iroot->addChild( g4 );
    iroot->updateVolume();
    endEditCP(iroot);

   
    // make the root and test objects

    points = GeoPositions3f::create();
    beginEditCP(points);
    points->addValue( Pnt3f(0,0,0) );
    points->addValue( Pnt3f(0,0,0) );
    points->addValue( Pnt3f(0,0,0) );
    points->addValue( Pnt3f(0,0,0) );
    points->addValue( Pnt3f(0,0,0) );
    endEditCP(points);

    GeoIndicesUI32Ptr index = GeoIndicesUI32::create();     
    beginEditCP(index);
    index->addValue( 0 );
    index->addValue( 1 );
    index->addValue( 2 );
    index->addValue( 3 );
    index->addValue( 4 );
    endEditCP(index);

    GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    beginEditCP(lens);
    lens->addValue( 2 );
    lens->addValue( 3 );
    endEditCP(lens);
    
    GeoPTypesPtr type = GeoPTypesUI8::create();     
    beginEditCP(type);
    type->addValue( GL_LINES );
    type->addValue( GL_TRIANGLES );
    endEditCP(type);

    GeometryPtr testgeocore = Geometry::create();
    beginEditCP(testgeocore);
    testgeocore->setPositions( points );
    testgeocore->setIndices( index );
    testgeocore->setLengths( lens );
    testgeocore->setTypes( type );
    testgeocore->setMaterial( red );
    endEditCP( testgeocore );
    
    
    NodePtr testgeo = Node::create();
    beginEditCP(testgeo);
    testgeo->setCore( testgeocore );
    endEditCP( testgeo );
    
    
    root = Node::create();
    GroupPtr rootc = Group::create();
    beginEditCP(root);
    root->setCore( rootc );
    root->addChild( iroot );
    root->addChild( testgeo );
    endEditCP( root );


    dact = DrawAction::create();

    dact->setFrustumCulling(false);

    glutMainLoop();
    
    return 0;
}

