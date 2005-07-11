#include <iostream>
#include <OSGGLUT.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGSimpleGeometry.h>
#include <OSGDirectionalLight.h>
#include <OSGViewport.h>
#include <OSGCamera.h>
#include <OSGWindow.h>
#include <OSGGLUTWindow.h>
#include <OSGCamera.h>
#include <OSGPerspectiveCamera.h>
#include <OSGSolidBackground.h>
#include <OSGDistanceLOD.h>
#include <OSGMaterial.h>
#include <OSGSimpleMaterial.h>
#include <OSGTrackball.h>

using namespace OSG;

DrawAction* drAct;
NodePtr root;
PerspectiveCameraPtr camera;
ViewportPtr viewp;
WindowPtr window;
TransformPtr cam_trans;//, lod_trans;
Trackball tball;
Matrix transMat;

int mouseb = 0;
int lastX=0, lastY=0;

/*
void display(void)
{
    Matrix m1, m2;
    Quaternion q1;
        
    float time = glutGet( GLUT_ELAPSED_TIME );
    m1.setTranslate( 0, 0, 2.5+(int)(time/100)%360/36.0 );
    q1.setValueAsAxisDeg( 0, 1, 0, (int) (time/100)%360 );
    m2.setRotate( q1 );
    m2.mult( m1 );
    cam_trans->getSFMatrix()->setValue( m2 );
    
    window->draw( drAct );
    
}
*/
    
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
    //transMat.setTranslate( 1, 0, 0 );
    cam_trans->getSFMatrix()->setValue( m1 );
    //lod_trans->getSFMatrix()->setValue( transMat );
    

    window->draw( drAct );
}


void
animate(void)
{
    glutPostRedisplay();
}

void resize( int w, int h )
{   
    window->resize( w, h );
}

void
motion(int x, int y)
{   
    Real32 w = window->getWidth(), h = window->getHeight();
    

    Real32  a = -2. * ( lastX / w - .5 ),
                b = -2. * ( .5 - lastY / h ),
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
    lastX = x;
    lastY = y;
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
    lastX = x;
    lastY = y;
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
        case 'r':   std::cerr << "Sending ray through " << x << "," << y << std::endl;
            Line l;
            camera->calcViewRay( l, x, y, *viewp );
            std::cerr << "From " << l.getPosition() << ", dir " << l.getDirection() << std::endl;
            break;
    }
}



int main(int argc, char** argv)
{
    std::cout << "osgInit()..." << std::endl;
    osgInit( argc, argv );
    
    std::cout << "glutInit()..." <<  std::endl;
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
    int winID = glutCreateWindow("OpenSG");
    
    glutKeyboardFunc(key);
    glutVisibilityFunc(vis);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);       
    glutMouseFunc(mouse);   
    glutMotionFunc(motion); 
    
    glutIdleFunc(display);
            
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glClearColor( .3, .3, .8, 1 );
    
    std::cout << "Creating objects..." << std::endl;
    
    //BEACON
    NodePtr beaconNode = Node::create();
    GroupPtr beaconCore = Group::create();
    beginEditCP( beaconNode );
    beaconNode->setCore( beaconCore );
    endEditCP( beaconNode );
    
    /*
    //LIGHT
    NodePtr dlightNode = Node::create();
    DirectionalLightPtr dlightCore = DirectionalLight::create();
    beginEditCP(dlightNode);
    dlightNode->setCore(dlightCore);
    endEditCP(dlightNode);
    
    beginEditCP(dlightCore);
    dlightCore->setAmbient( .3, .3, .3, 1 );
    dlightCore->setDiffuse( .5, .5, .5, 1 );
    dlightCore->setDirection( 0, 0 , 1 );
    dlightCore->setBeacon( beaconNode );
    endEditCP(dlightCore);
    */
        
    //TRANSFORM
    NodePtr transNode = Node::create();
    TransformPtr transCore = Transform::create();
    beginEditCP( transNode );
    transNode->setCore( transCore );
    transNode->addChild( beaconNode );
    endEditCP( transNode );
    cam_trans = transCore;
    
    //LOD
    NodePtr lowDetailNode = makeBox( 1,1,1, 1,1,1 );
    GeometryPtr boxCore = GeometryPtr::dcast(lowDetailNode->getCore());
    SimpleMaterialPtr lowDetailMat = SimpleMaterial::create();
    lowDetailMat->setDiffuse( Color3f( 1,0,0 ) );
    lowDetailMat->setAmbient( Color3f( 1,0,0 ) );
    boxCore->setMaterial( lowDetailMat );
    
    NodePtr     medDetailNode = makeSphere( 1, 1 );
    GeometryPtr medSphereCore = GeometryPtr::dcast(medDetailNode->getCore());
    SimpleMaterialPtr medDetailMat = SimpleMaterial::create();
    medDetailMat->setDiffuse( Color3f( 0,1,0 ) );
    medDetailMat->setAmbient( Color3f( 0,1,0 ) );
    medSphereCore->setMaterial( medDetailMat );
    
    NodePtr highDetailNode = makeSphere( 2, 1 );
    GeometryPtr highSphereCore = GeometryPtr::dcast(highDetailNode->getCore());
    SimpleMaterialPtr highDetailMat = SimpleMaterial::create();
    highDetailMat->setDiffuse( Color3f( 0,0,1 ) );
    highDetailMat->setAmbient( Color3f( 0,0,1 ) );
    highDetailMat->setSpecular( Color3f(1, 1, 1) );
    highDetailMat->setShininess( 10 );
    highSphereCore->setMaterial( highDetailMat );
    
    NodePtr lodNode = Node::create();
    DistanceLODPtr lodNodeCore = DistanceLOD::create();
    beginEditCP(lodNode);
    lodNode->setCore(lodNodeCore);
    lodNode->addChild( highDetailNode );
    lodNode->addChild( medDetailNode );
    lodNode->addChild( lowDetailNode );
    endEditCP(lodNode);
    
    beginEditCP(lodNodeCore);
    lodNodeCore->getSFCenter()->setValue( Pnt3f(0, 0, 2) );
    lodNodeCore->getMFRange()->push_back( 4.0 );
    lodNodeCore->getMFRange()->push_back( 8.0 );
    lodNodeCore->getMFRange()->push_back( 11.0 );
    endEditCP(lodNodeCore);
    
        
    //TRANSFORM LOD
    NodePtr transLODNode = Node::create();
    TransformPtr transLODCore = Transform::create();
    transMat.setTranslate( 1, -1, -1 );
    beginEditCP(transLODCore);
    transLODCore->getSFMatrix()->setValue( transMat );
    endEditCP(transLODCore);
    beginEditCP( transLODNode );
    transLODNode->setCore( transLODCore );
    transLODNode->addChild( lodNode );
    endEditCP( transLODNode );
    
    
        
    //ROOT
    root = Node::create();
    GroupPtr rootCore = Group::create();
    beginEditCP(root);
    root->setCore(rootCore);
    root->addChild(transNode);
    root->addChild(transLODNode);
    endEditCP(root);
    
    
    
    camera = PerspectiveCamera::create();
    beginEditCP(camera);
    camera->setBeacon( beaconNode );
    camera->setFov( deg2rad(90) );
    camera->setNear( 0.1 );
    camera->setFar( 10000 );
    endEditCP(camera);
    
    SolidBackgroundPtr background = SolidBackground::create();
    
    viewp = Viewport::create();
    beginEditCP(viewp);
    viewp->setCamera( camera );
    viewp->setBackground( background );
    viewp->setRoot( root );
    viewp->setSize( 0,0, 1,1 );
    endEditCP(viewp);
    
    GLint glVP[4];
    glGetIntegerv( GL_VIEWPORT, glVP );
    
    GLUTWindowPtr gwin = GLUTWindow::create();
    gwin->setId(winID);
    gwin->setSize(glVP[2], glVP[3]);
    
    window = gwin;
    beginEditCP(window);
    window->addPort( viewp );
    window->init();
    endEditCP(window);
    
    drAct = DrawAction::create();
    
    Vec3f pos( 0, 0, 3 );
    tball.setMode( Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( Trackball::OSGFree );

    glutMainLoop();
    return 0;
}
