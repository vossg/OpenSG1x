#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <GL/glut.h>

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
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>          
#include <OSGAction.h>
#include <OSGDrawAction.h>
//#include <OSGGeometry.h>
#include <OSGSceneFileHandler.h>

#include <OSGDirectionalLight.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGGLUTWindow.h"
//#include "OSGPipe.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGBackground.h"
#include "OSGSolidBackground.h"
//#include "OSGVariedBackground.h"
#include "OSGSolidBackground.h"
#include "OSGGradientBackground.h"
#include "OSGDynamicBackground.h"
//#include "OSGUniformBackground.h"

#if defined(__linux) || ( defined(WIN32) && ! defined(OSG_BUILD_DLL) )
#include "RAW/OSGRAWSceneFileType.h"
#endif

#include "OSGTrackball.h"

using namespace OSG;

DrawAction * ract;

NodePtr  root;

NodePtr  file;

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
    
//    cout << "TBROT" << endl << tball.getRotation() << endl;
//    cout << "M3" << endl << m3 << endl;
//    cout << "Q1" << endl << q1 << endl;
//    cout << "M1" << endl << m1 << endl;

//  m1.setRotate( tball.getRotation() );
    m2.setTranslate( tball.getPosition() );
    
//cout << "Pos: " << tball.getPosition() << ", Rot: " << tball.getRotation() << endl;

//    cout << tball.getRotation() << endl;

    m1.mult( m2 );
    cam_trans->getSFMatrix()->setValue( m1 );

    win->draw( ract );
}

void reshape( int w, int h )
{
    cerr << "Reshape: " << w << "," << h << endl;
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
                cerr << "Lighting disabled." << endl;
                break;
    case 's':   glEnable( GL_LIGHTING );
                cerr << "Lighting enabled." << endl;
                break;
    case 'z':   glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
                cerr << "PolygonMode: Point." << endl;
                break;
    case 'x':   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
                cerr << "PolygonMode: Line." << endl;
                break;
    case 'c':   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
                cerr << "PolygonMode: Fill." << endl;
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

    // root
    root = Node::create();
    GroupPtr gr1 = Group::create();
    beginEditCP(root);
    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );
    endEditCP(root);

    // Load the file

    NodePtr file = SceneFileHandler::the().read(argv[1]);

    file->updateVolume();

    // should check first. ok for now.
    const BoxVolume *vol = (BoxVolume *)&file->getVolume();

    Vec3f min,max;
    vol->getBounds( min, max );
    
    cout << "Volume: from " << min << " to " << max << endl;

    beginEditCP(dlight);
    dlight->addChild( file );
    endEditCP(dlight);
    
    // Camera
    PerspectiveCameraPtr cam = PerspectiveCamera::create();

    cam->setBeacon( b1n );
    cam->setFov( deg2rad( 60 ) );
    cam->setNear( 0.1 );
    cam->setFar( 10000 );

    // Background
//  BackgroundPtr bkgnd = Background::create();
//  SolidBackgroundPtr sbkgnd = SolidBackground::create();
//  VariedBackgroundPtr vbkgnd = VariedBackground::create();
//  ColorBackgroundPtr cbkgnd = ColorBackground::create();
//  GradientBackgroundPtr gbkgnd = GradientBackground::create();
    DynamicBackgroundPtr gbkgnd = DynamicBackground::create();

//      sbkgnd->setColor( 0,0,1 );
/*
//      vbkgnd->setCol( 0, 0, 1 );
        vbkgnd->setX( 0 );
//      vbkgnd->setCol( 0, 0, 1 );
        vbkgnd->setX( 0.5 );
//      vbkgnd->setCol( 0, 1, 0 );
        vbkgnd->setX( 1 );
*/
/*
    cbkgnd->setColor( Color3f(1, 0, 0) );
    cbkgnd->setPosition( 0 );
    cbkgnd->setColor( Color3f(0, 0, 1) );
    cbkgnd->setPosition( 0.5 );
    cbkgnd->setColor( Color3f(0, 1, 0) );
    cbkgnd->setPosition( 1 );
*/
/*
    gbkgnd->addColor( Color3f(1, 0, 0), -0.9 );
    gbkgnd->addColor( Color3f(0, 1, 0), 0.2 );
    gbkgnd->addColor( Color3f(0, 0, 1), -0.3 );
    gbkgnd->addColor( Color3f(0, 1, 1), 0.4 );
    gbkgnd->addColor( Color3f(0, 1, 0), 1.5 );
    gbkgnd->addColor( Color3f(1, 1, 0), -0.6 );
    gbkgnd->addColor( Color3f(0, 1, 0), 1.5 );
    gbkgnd->addColor( Color3f(1, 1, 0), 0.1 ); 
    gbkgnd->addColor( Color3f(1, 0, 0), 0.5 );
    gbkgnd->addColor( Color3f(0, 0, 1), 1.8 );
    gbkgnd->addColor( Color3f(0, 0, 1), 0.91 );
*/
/*  gbkgnd->addColors( Color3f(0, 1, 0), 180 );
    gbkgnd->addColors( Color3f(0, 1, 1), 135 );
    gbkgnd->addColors( Color3f(0, 0, 1), 105 );
    gbkgnd->addColors( Color3f(1, 0, 1), 90 );
    gbkgnd->addColors( Color3f(1, 0, 0), 80 );
//  gbkgnd->addColors( Color3f(0, 0, 1), 60 );
    gbkgnd->addColors( Color3f(1, 1, 0), 40 );
    gbkgnd->addColors( Color3f(1, 1, 1), 0 );
    gbkgnd->addColors( Color3f(1, 1, 0), 40 );
    gbkgnd->addColors( Color3f(1, 0, 0), 80 );
    gbkgnd->addColors( Color3f(1, 0, 1), 90 );
    gbkgnd->addColors( Color3f(0, 0, 1), 105 );
    gbkgnd->addColors( Color3f(0, 1, 1), 135 );
    gbkgnd->addColors( Color3f(0, 1, 0), 180 );
*/

    gbkgnd->addColor( Color3f(0, 0, 0), 190 );
    gbkgnd->addColor( Color3f(1, 1, 0), 40 );
    gbkgnd->addColor( Color3f(0, 0, 1), 105 );
    gbkgnd->addColor( Color3f(0, 1, 0), 180 );
    gbkgnd->addColor( Color3f(1, 0, 0), 80 );
    gbkgnd->addColor( Color3f(0, 0, 0), 500 );
    gbkgnd->addColor( Color3f(0, 0, 0), -100 );
    gbkgnd->addColor( Color3f(1, 0, 1), 90 );
    gbkgnd->addColor( Color3f(1, 1, 1), 0 );
    gbkgnd->addColor( Color3f(0, 1, 1), 135 );
    gbkgnd->addColor( Color3f(0, 0, 0), -2 );


    // Viewport

    ViewportPtr vp = Viewport::create();
    vp->setCamera( cam );
//  vp->setBackground( bkgnd );
//  vp->setBackground( sbkgnd );
//  vp->setBackground( cbkgnd );
    vp->setBackground( gbkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );

    // Window
    cout << "GLUT winid: " << winid << endl;

    GLUTWindowPtr gwin;

    GLint glvp[4];
    glGetIntegerv( GL_VIEWPORT, glvp );

    gwin = GLUTWindow::create();
    gwin->setWinID(winid);
    gwin->setSize( glvp[2], glvp[3] );

    win = gwin;

    win->addPort( vp );

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

