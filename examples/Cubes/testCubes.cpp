#include <OpenSG/OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <GL/glut.h>

#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGMatrix.h>

#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGTransform.h>

#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGDrawAction.h>

#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGSimpleMaterial.h>

#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGSolidBackground.h>

#include <OpenSG/OSGTrackball.h>

#include "OSGCubes.h"

// little helper to create a random number between a and b
#define random( a, b ) \
( ( rand() / float(RAND_MAX) ) * ( (b) - (a) ) + (a) )

using namespace OSG;

DrawAction * ract;

NodePtr  root;

NodePtr  file;

PerspectiveCameraPtr cam;
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
    
    m2.setTranslate( tball.getPosition() );
    
    m1.mult( m2 );

    beginEditCP( cam_trans );
    cam_trans->setMatrix( m1 );
    endEditCP( cam_trans );

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

// tball stuff


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
    case 27:    exit(0);
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
    case 'r':   cerr << "Sending ray through " << x << "," << y << endl;
                Line l;
                cam->calcViewRay( l, x, y, *vp );
                cerr << "From " << l.getPosition() << ", dir " << l.getDirection() << endl;
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
    
    // a little OpenGL initialization
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial( GL_FRONT_AND_BACK, GL_DIFFUSE );

    // create the graph

    // transformation
    // this transformation is manipulated by the trackball
    // it is also the beacon for camera and light   
    // using the same for camera and light specifies the light in the camera space
    // and gives a headlight effect

    NodePtr t1n = Node::create();
    TransformPtr t1 = Transform::create();
    beginEditCP(t1n);
    t1n->setCore( t1 );
    endEditCP(t1n);

    cam_trans = t1;

    // Create the cubes' material
    
    SimpleMaterialPtr mat = SimpleMaterial::create();
    
    beginEditCP(mat);
    mat->setDiffuse( Color3f(1,0,0) );
    mat->setAmbient( Color3f(.2,0,0) );
    mat->setSpecular( Color3f(1,1,1) );
    mat->setShininess( 10 );
    endEditCP(mat);
    
    // Create the Cubes node

    NodePtr cnode = Node::create();
    CubesPtr cubes = Cubes::create();

    beginEditCP(cubes);
    cubes->setMaterial( mat );  
    
    // create a bunch of random cubes
    
    for ( int i=0; i < 10; i++ )
    {
        cubes->getMFPosition()->addValue( Pnt3f( random(-2, 2), 
                                                 random(-2, 2), 
                                                 random(-2, 2)) );
        cubes->getMFLength()->addValue( random(0.5, 2) );
        cubes->getMFColor()->addValue( Color3f( random(0.5, 1), 
                                                random(0.5, 1), 
                                                random(0.5, 1)) );
    }
    
    endEditCP(cubes);

    beginEditCP(cnode);
    cnode->setCore( cubes );
    endEditCP(cnode);

    // light
    
    NodePtr dlight = Node::create();
    DirectionalLightPtr dl = DirectionalLight::create();

    beginEditCP(dlight);
    dlight->setCore( dl );
    dlight->addChild( cnode );  
    endEditCP(dlight);
    
    beginEditCP(dl);
    dl->setAmbient( .3, .3, .3, 1 );
    dl->setDiffuse( 1, 1, 1, 1 );
    dl->setDirection( 0, 0, 1 );
    dl->setBeacon( t1n );
    endEditCP(dl);

    // root
    root = Node::create();
    GroupPtr gr1 = Group::create();
    beginEditCP(root);
    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );
    endEditCP(root);
    
    // Camera
    
    cam = PerspectiveCamera::create();
    beginEditCP(cam);
    cam->setBeacon( t1n );
    cam->setFov( deg2rad( 90 ) );
    cam->setNear( 0.1 );
    cam->setFar( 10000 );
    endEditCP(cam);

    // Background
    SolidBackgroundPtr bkgnd = SolidBackground::create();

    beginEditCP(bkgnd);
    bkgnd->setColor( Color3f(.2, .2, .8) );
    endEditCP(bkgnd);

    // Viewport

    vp = Viewport::create();
    beginEditCP(vp);
    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );
    endEditCP(vp);

    // Window

    GLUTWindowPtr gwin;

    GLint glvp[4];
    glGetIntegerv( GL_VIEWPORT, glvp );

    gwin = GLUTWindow::create();
    beginEditCP(gwin);
    gwin->setWinID(winid);
    gwin->setSize( glvp[2], glvp[3] );
    endEditCP(gwin);

    win = gwin;

    beginEditCP(win);
    win->addPort( vp );
    endEditCP(win);
    
    win->init();

    // Action
    
    ract = DrawAction::create();

    // tball

    // update the scene's bounding volume

    Vec3f min,max;
    root->updateVolume();
    root->getVolume().getBounds( min, max );
    
    cout << "Volume: from " << min << " to " << max << endl;
    
    Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5 );

    tball.setMode( Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( Trackball::OSGFree );

    // run...
    
    glutMainLoop();
    
    return 0;
}

