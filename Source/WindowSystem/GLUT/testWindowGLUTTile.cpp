#include <OSGConfig.h>

#include <iostream>

#include<ctype.h>

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
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGSimpleGeometry.h>
#include <OSGSceneFileHandler.h>

#include <OSGDirectionalLight.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGTileCameraDecorator.h"
#include "OSGWindow.h"
#include "OSGGLUTWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGBackground.h"
#include "OSGSkyBackground.h"
#include "OSGSolidBackground.h"

//#include <OSGOSGWriter.h>

#include "OSGTrackball.h"

using namespace OSG;

DrawAction * ract;

NodePtr  root;

NodePtr  file;

PerspectiveCameraPtr cam;
int nhviewports = 2, nvviewports = 2;
ViewportPtr *vp;
TileCameraDecoratorPtr *deco;
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

void key(unsigned char key, int , int )
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
    case 'd':   {
                    
                for ( int i = 0; i < nhviewports; i++ )
                {
                    for ( int j = 0; j < nvviewports; j++ )
                    {
                        int ind = i * nvviewports + j;
                        beginEditCP(deco[ind]);
                        deco[ind]->setSize( 0, 0, 1, 1 );
                        endEditCP(deco[ind]);
                    }
                }
                }
                break;
    case 'f':   {
                    
                for ( int i = 0; i < nhviewports; i++ )
                {
                    for ( int j = 0; j < nvviewports; j++ )
                    {
                        int ind = i * nvviewports + j;

                        beginEditCP(deco[ind]);
                        deco[ind]->setSize( 1./nhviewports * i,1./nvviewports * j, 
                                            1./nhviewports * (i+1),1./nvviewports * (j+1) );
                        endEditCP(deco[ind]);
                    }
                }
                }
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


    if ( argc > 1 && isdigit(argv[1][0]) )
    {
        nhviewports = atoi( argv[1] );
        argv++;
        argc--;
    }
    if ( argc > 1 && isdigit(argv[1][0]) )
    {
        nvviewports = atoi( argv[1] );
        argv++;
        argc--;
    }
    else
        nvviewports = nhviewports;
        
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

    NodePtr file = NullFC;
    
    if ( argc > 1 )
        file = SceneFileHandler::the().read(argv[1]);
    
    if ( file == NullFC )
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        file = makeTorus( .5, 2, 16, 16 );
        file = makeBox( 1,1,1, 1,1,1 );
    }
    
    file->updateVolume();

    Vec3f min,max;
    file->getVolume().getBounds( min, max );
    
    std::cout << "Volume: from " << min << " to " << max << std::endl;

    beginEditCP(dlight);
    dlight->addChild( file );
    endEditCP(dlight);

    std::cerr << "Tree: " << std::endl;
    root->dump();

    // Camera
    
    cam = PerspectiveCamera::create();
    cam->setBeacon( b1n );
    cam->setFov( deg2rad( 90 ) );
    cam->setNear( 0.1 );
    cam->setFar( 100 );

    // Background
#if 1 // doesn't work right now
    SkyBackgroundPtr sbkgnd = SkyBackground::create();


    sbkgnd->getMFSkyColor()->push_back(Color4f(1, 0, 0,0.5));
    sbkgnd->getMFSkyAngle()->push_back(Pi / 2);
    sbkgnd->getMFSkyColor()->push_back(Color4f(0, 1, 0,0.5));
    sbkgnd->getMFSkyAngle()->push_back(Pi);
    sbkgnd->getMFSkyColor()->push_back(Color4f(0, 0, 1,0.5)); 

#else
    SolidBackgroundPtr sbkgnd = SolidBackground::create();
    sbkgnd->setColor( Color3f(.5, .5, 1) );
#endif
    
    // Window
    std::cout << "GLUT winid: " << winid << std::endl;

    GLUTWindowPtr gwin;

    GLint glvp[4];
    glGetIntegerv( GL_VIEWPORT, glvp );

    gwin = GLUTWindow::create();
    gwin->setId(winid);
    gwin->setSize( glvp[2], glvp[3] );

    win = gwin;

    // Viewports & Decorators

    vp = new ViewportPtr [ nhviewports * nvviewports ];
    deco = new TileCameraDecoratorPtr [ nhviewports * nvviewports ];
    
    for ( int i = 0; i < nhviewports; i++ )
    {
        for ( int j = 0; j < nvviewports; j++ )
        {
            int ind = i * nvviewports + j;
            vp[ind] = Viewport::create();
            vp[ind]->setBackground( sbkgnd );
            vp[ind]->setRoot( root );
            vp[ind]->setSize(   1./nhviewports * i,1./nvviewports * j, 
                                1./nhviewports * (i+1),1./nvviewports * (j+1) );

            deco[ind] = TileCameraDecorator::create();
            deco[ind]->setDecoratee( cam );
            deco[ind]->setSize( 1./nhviewports * i,1./nvviewports * j, 
                                1./nhviewports * (i+1),1./nvviewports * (j+1) );

            deco[ind]->setFullSize( 800, 800 );

            vp[ind]->setCamera( deco[ind] );
            // for debugging: vp[ind]->setCamera( cam );

            win->addPort( vp[ind] );
        }
    }

    win->init();

#if 0
    // Test write, to check generic access
    
    ofstream outFileStream( "test.osg" );
    if( !outFileStream )
    {
        std::cerr << "Can not open output stream to file" << std::endl;
        return -1;
    }

    OSGWriter writer( outFileStream, 4 );
    writer.write( win );
 
    
#endif
    
    // Action
    
    ract = DrawAction::create();
    ract->setFrustumCulling( false );
    
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

