#include <OSGConfig.h>

#include <iostream>

#include <OSGGLUT.h>

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGBoxVolume.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGSimpleGeometry.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGIntersectAction.h>
#include <OSGSimpleMaterial.h>
#include <OSGGeoProperty.h>
#include <OSGGeometry.h>
#include <OSGTriangleIterator.h>
#include <OSGSceneFileHandler.h>

#include <OSGDirectionalLight.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGGLUTWindow.h"
//#include "OSGPipe.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGOrthographicCamera.h"
#include "OSGSolidBackground.h"
//#include "OSGUniformBackground.h"

#if defined(__linux) || ( defined(WIN32) && ! defined(OSG_BUILD_DLL) )
#include "OSGRAWSceneFileType.h"
#endif

#include "OSGTrackball.h"

using namespace OSG;

DrawAction * ract;

NodePtr  root;
NodePtr  iroot;

NodePtr  file;

GeoPositions3fPtr isect_points;

CameraPtr cam;
PerspectiveCameraPtr pcam;
OrthographicCameraPtr ocam;
ViewportPtr vp;
WindowPtr win;

TransformPtr cam_trans;

Trackball tball;

int mouseb = 0;
int lastx=0, lasty=0;

void 
display(void)
{
    Matrix m1, m2, m3;
    Quaternion q1;

    tball.getRotation().getValue(m3);

    q1.setValue(m3);

    m1.setRotate(q1);
    
//    std::cout << "TBROT" << std::endl << tball.getRotation() << std::endl;
//    std::cout << "M3" << std::endl << m3 << std::endl;
//    std::cout << "Q1" << std::endl << q1 << std::endl;
//    std::cout << "M1" << std::endl << m1 << std::endl;

//  m1.setRotate( tball.getRotation() );
    m2.setTranslate( tball.getPosition() );
    
//std::cout << "Pos: " << tball.getPosition() << ", Rot: " << tball.getRotation() << std::endl;

//    std::cout << tball.getRotation() << std::endl;

    m1.mult( m2 );
    cam_trans->getSFMatrix()->setValue( m1 );

    win->draw( ract );
}

void reshape( int w, int h )
{
    std::cerr << "Reshape: " << w << "," << h << std::endl;
    win->resize( w, h );
}


void
animate(void)
{
    glutPostRedisplay();
}

// tballall stuff


void
motion(int x, int y)
{   
    Real32 w = win->getWidth(), h = win->getHeight();
    

    Real32  a = -2. * ( lastx / w - .5 ),
                b = -2. * ( .5 - lasty / h ),
                c = -2. * ( x / w - .5 ),
                d = -2. * ( .5 - y / h );

    if ( mouseb & ( 1 << GLUT_LEFT_BUTTON ) )
    {
        tball.updateRotation( a, b, c, d );     
    }
    else if ( mouseb & ( 1 << GLUT_MIDDLE_BUTTON ) )
    {
        tball.updatePosition( a, b, c, d );     
    }
    else if ( mouseb & ( 1 << GLUT_RIGHT_BUTTON ) )
    {
        tball.updatePositionNeg( a, b, c, d );  
    }
    lastx = x;
    lasty = y;
}

void
mouse(int button, int state, int x, int y)
{
    if ( state == 0 )
    {
        switch ( button )
        {
        case GLUT_LEFT_BUTTON:  break;
        case GLUT_MIDDLE_BUTTON:tball.setAutoPosition(true);
                                break;
        case GLUT_RIGHT_BUTTON:     tball.setAutoPositionNeg(true);
                                break;
        }
        mouseb |= 1 << button;
    }
    else if ( state == 1 )
    {
        switch ( button )
        {
        case GLUT_LEFT_BUTTON:  break;
        case GLUT_MIDDLE_BUTTON:tball.setAutoPosition(false);
                                break;
        case GLUT_RIGHT_BUTTON:     tball.setAutoPositionNeg(false);
                                break;
        }       
        mouseb &= ~(1 << button);
    }
    lastx = x;
    lasty = y;
}

void
vis(int visible)
{
    if (visible == GLUT_VISIBLE) 
    {
        glutIdleFunc(animate);
    } 
    else 
    {
        glutIdleFunc(NULL);
    }
}

void key(unsigned char key, int x, int y)
{
    switch ( key )
    {
    case 27:    osgExit(); exit(0);
    case 'a':   glDisable( GL_LIGHTING );
                std::cerr << "Lighting disabled." << std::endl;
                break;
    case 's':   glEnable( GL_LIGHTING );
                std::cerr << "Lighting enabled." << std::endl;
                break;
    case 'z':   glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
                std::cerr << "PolygonMode: Point." << std::endl;
                break;
    case 'x':   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
                std::cerr << "PolygonMode: Line." << std::endl;
                break;
    case 'c':   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
                std::cerr << "PolygonMode: Fill." << std::endl;
                break;
    case 'p':   cam = pcam;
                vp->setCamera( cam );
                std::cerr << "Perspective Camera." << std::endl;
                break;
    case 'o':   cam = ocam;
                vp->setCamera( ocam );
                std::cerr << "Orthographic Camera." << std::endl;
                break;
    case 'r':   std::cerr << "Sending ray through " << x << "," << y << std::endl;
                Line l;
                cam->calcViewRay( l, x, y, *vp );
                std::cerr << "From " << l.getPosition() << ", dir " << l.getDirection() << std::endl;
    
                IntersectAction *act = IntersectAction::create();
                
                act->setLine( l );
            
                act->apply( iroot );
            
                beginEditCP(isect_points);
                isect_points->setValue( l.getPosition(), 0 );
                isect_points->setValue( l.getPosition() + l.getDirection(), 1 );
            
                if ( act->didHit() )
                {
                    std::cerr << " object " << act->getHitObject() 
                         << " tri " << act->getHitTriangle() 
                         << " at " << act->getHitPoint();
            
                    isect_points->setValue( l.getPosition() + 
                            l.getDirection() * act->getHitT(), 1 );
                    
                    TriangleIterator it( act->getHitObject() );
                    it.seek( act->getHitTriangle() );
                    
                    Matrix m;
                    act->getHitObject()->getToWorld(m);
            
                    Pnt3f p = it.getPosition(0);
                    m.multMatrixPnt( p );
                    isect_points->setValue( p, 2 );
                    p = it.getPosition(1);
                    m.multMatrixPnt( p );
                    isect_points->setValue( p, 3 );
                    p = it.getPosition(2);
                    m.multMatrixPnt( p );
                    isect_points->setValue( p, 4 );
                }
                else
                {
                    isect_points->setValue( Pnt3f(0,0,0), 2 );
                    isect_points->setValue( Pnt3f(0,0,0), 3 );
                    isect_points->setValue( Pnt3f(0,0,0), 4 );
                }
                endEditCP(isect_points);
            
                std::cerr << std::endl;
            
                glutPostRedisplay();
                break;
    }
}


int main (int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");
    glutKeyboardFunc(key);
    glutVisibilityFunc(vis);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);       
    glutMouseFunc(mouse);   
    glutMotionFunc(motion); 
    
    glutIdleFunc(display);  

    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    // OSG

    SceneFileHandler::the().print();

    // create the graph

    // beacon for camera and light  
    NodePtr b1n = Node::create();
    GroupPtr b1 = Group::create();
    beginEditCP(b1n);
    b1n->setCore( b1 );
    endEditCP(b1n);

    // transformation
    NodePtr t1n = Node::create();
    TransformPtr t1 = Transform::create();
    beginEditCP(t1n);
    t1n->setCore( t1 );
    t1n->addChild( b1n );
    endEditCP(t1n);

    cam_trans = t1;

    // light
    
    NodePtr dlight = Node::create();
    DirectionalLightPtr dl = DirectionalLight::create();

    beginEditCP(dlight);
    dlight->setCore( dl );
    endEditCP(dlight);
    
    beginEditCP(dl);
    dl->setAmbient( .3, .3, .3, 1 );
    dl->setDiffuse( 1, 1, 1, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);
    endEditCP(dl);

    // intersect geometry

    SimpleMaterialPtr white = SimpleMaterial::create();
    SimpleMaterialPtr red = SimpleMaterial::create();
    
    white->setEmission( Color3f( 1,1,1 ) );
    red->setEmission( Color3f( 1,0,0 ) );   

    isect_points = GeoPositions3f::create();
    beginEditCP(isect_points);
    isect_points->addValue( Pnt3f(0,0,0) );
    isect_points->addValue( Pnt3f(0,0,0) );
    isect_points->addValue( Pnt3f(0,0,0) );
    isect_points->addValue( Pnt3f(0,0,0) );
    isect_points->addValue( Pnt3f(0,0,0) );
    endEditCP(isect_points);

    GeoIndicesUI32Ptr index = GeoIndicesUI32::create();     
    beginEditCP(index);
    index->addValue( 0 );
    index->addValue( 1 );
    index->addValue( 2 );
    index->addValue( 3 );
    index->addValue( 4 );
    endEditCP(index);

    GeoPLengthsUI32Ptr lens = GeoPLengthsUI32::create();    
    beginEditCP(lens);
    lens->addValue( 2 );
    lens->addValue( 3 );
    endEditCP(lens);
    
    GeoPTypesUI8Ptr type = GeoPTypesUI8::create();  
    beginEditCP(type);
    type->addValue( GL_LINES );
    type->addValue( GL_TRIANGLES );
    endEditCP(type);

    GeometryPtr testgeocore = Geometry::create();
    beginEditCP(testgeocore);
    testgeocore->setPositions( isect_points );
    testgeocore->setIndices( index );
    testgeocore->setLengths( lens );
    testgeocore->setTypes( type );
    testgeocore->setMaterial( red );
    endEditCP( testgeocore );
    
    
    NodePtr testgeo = Node::create();
    beginEditCP(testgeo);
    testgeo->setCore( testgeocore );
    endEditCP( testgeo );
    

    // root
    root = Node::create();
    GroupPtr gr1 = Group::create();
    beginEditCP(root);
    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );
    root->addChild( testgeo );
    endEditCP(root);

    // Load the file

    NodePtr file = NullFC;
    
    if ( argc > 1 )
        file = SceneFileHandler::the().read(argv[1]);
    
    if ( file == NullFC )
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        file = makeTorus( .5, 2, 16, 16 );
    }
    
    file->updateVolume();

    Vec3f min,max;
    file->getVolume().getBounds( min, max );
    
    std::cout << "Volume: from " << min << " to " << max << std::endl;

    beginEditCP(dlight);
    dlight->addChild( file );
    endEditCP(dlight);

    // Intersect the loaded file only
    iroot = file;

    std::cerr << "Tree: " << std::endl;
    root->dump();

    // Cameras
    
    pcam = PerspectiveCamera::create();
    pcam->setBeacon( b1n );
    pcam->setFov( deg2rad( 90 ) );
    pcam->setNear( 0.1 );
    pcam->setFar( 10000 );
    
    ocam = OrthographicCamera::create();
    ocam->setBeacon( b1n );
    ocam->setVerticalSize((max-min).length());
    ocam->setNear( 0.1 );
    ocam->setFar( 10000 );

    cam = pcam;
    
    // Background
    SolidBackgroundPtr bkgnd = SolidBackground::create();
    
    //bkgnd->setColor( 0,0,1 );

    // Viewport

    vp = Viewport::create();
    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );

    // Window
    std::cout << "GLUT winid: " << winid << std::endl;

    GLUTWindowPtr gwin;

    GLint glvp[4];
    glGetIntegerv( GL_VIEWPORT, glvp );

    gwin = GLUTWindow::create();
    gwin->setId(winid);
    gwin->setSize( glvp[2], glvp[3] );

    win = gwin;

    win->addPort( vp );

    win->init();

    // Action
    
    ract = DrawAction::create();

    // tball

    Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5 );

    tball.setMode( Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( Trackball::OSGFree );

    // run...
    
    glutMainLoop();
    
    return 0;
}

