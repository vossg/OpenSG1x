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
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGRenderAction.h>
#include <OSGGeometry.h>
#include <OSGGeoFunctions.h>

#include <OSGDirectionalLight.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGGLUTWindow.h"
//#include "OSGPipe.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
#include "OSGSceneFileHandler.h"

#include "OSGTrackball.h"

#include "OSGVRMLFile.h"

OSG::RenderAction * ract;
bool doWire = false;

OSG::NodePtr  root;

OSG::NodePtr  file;

OSG::WindowPtr win;

OSG::TransformPtr cam_trans;

OSG::Trackball tball;

int mouseb = 0;
int lastx=0, lasty=0;

int iNumFrames = 0;
int iMaxNumFrames = 5;

OSG::DirectionalLightPtr dl;

#define INTERACTIVE

void 
display(void)
{
/*
    OSG::Matrix m1, m2;

    m1.setRotate( tball.getRotation() );
    m2.setTranslate( tball.getPosition() );
    
    m1.mult( m2 );
    cam_trans->getSFMatrix()->setValue( m1 );
    */

    cam_trans->getSFMatrix()->setValue(tball.getFullTrackballMatrix());

#ifndef INTERACTIVE
    fprintf(stderr, "Frame %d\n", iNumFrames);
#endif
    win->render( ract );

#ifndef INTERACTIVE
    if(iNumFrames >= iMaxNumFrames)
    {
        sleep(5);
        OSG::osgExit(); 
        exit(0);
    }
    else
    {
        ++iNumFrames;
    }
#endif

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
    OSG::Real32 w = win->getWidth(), h = win->getHeight();
    

    OSG::Real32     a = -2. * ( lastx / w - .5 ),
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
#ifdef darwin
    int iMod = glutGetModifiers();

    if(iMod == GLUT_ACTIVE_SHIFT)
    {
        fprintf(stderr, "S Active\n");

        button = 1;
    }
    else if(iMod == GLUT_ACTIVE_CTRL)
    {
        fprintf(stderr, "C Active\n");

        button = 2;
    }
#endif

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

OSG::Action::ResultE calcVNormal( OSG::CNodePtr &, OSG::Action * action )
{
    OSG::NodePtr node = action->getActNode();
    OSG::GeometryPtr g = OSG::GeometryPtr::dcast( node->getCore() );

    if ( g->getNormals() == OSG::NullFC )
    {
        OSG::calcVertexNormals( g );
    }   
    
    return OSG::Action::Continue;
}

void key(unsigned char key, int, int)
{
    switch ( key )
    {
        case 27:    
            OSG::osgExit(); exit(0);
        case 'a':   
            glDisable( GL_LIGHTING );
            std::cerr << "Lighting disabled." << std::endl;
            break;
        case 's':   
            glEnable( GL_LIGHTING );
            std::cerr << "Lighting enabled." << std::endl;
            break;
        case 'z':   
            glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
            std::cerr << "PolygonMode: Point." << std::endl;
            break;
        case 'x':   
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
            std::cerr << "PolygonMode: Line." << std::endl;
            break;
        case 'c':   
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
            std::cerr << "PolygonMode: Fill." << std::endl;
            break;
        case 'w':   
            doWire = !doWire;
            std::cerr << "BBox render: " << (doWire?"on":"off") << std::endl;
            break;
        case 'd':
            root->dump(0, 0);
            break;
        case 'v':
            glEnable(GL_COLOR_MATERIAL);
            std::cerr << "Color material on" << std::endl;
            break;
        case 'V':
            glDisable(GL_COLOR_MATERIAL);
            std::cerr << "Color material off" << std::endl;
            break;
        case 'b':     
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            std::cerr << "Blending on" << std::endl;
            break;
        case 'B':     
            glDisable(GL_BLEND);
            std::cerr << "Blending off" << std::endl;
            break;
        case 'f':     
            ract->setFrustumCulling(true);
            std::cerr << "Frustum cull on" << std::endl;
            break;
        case 'F':     
            ract->setFrustumCulling(false);            
            std::cerr << "Frustum cull off" << std::endl;
            break;
            
        case '1':
            dl->setDirection(0,0,1);
            break;
        case '2':
            dl->setDirection(0,0,-1);
            break;
                
        case '3':
            dl->setDirection(0,1,0);
            break;
        case '4':
            dl->setDirection(0,-1,0);
            break;

        case '5':
            dl->setDirection(1,0,0);
            break;
        case '6':
            dl->setDirection(-1,0,0);
            break;
    }
}


int main (int argc, char **argv)
{
    OSG::osgInit(argc,argv);

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
    glEnable( GL_NORMALIZE );
    glEnable( GL_BLEND);
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    // OSG

    // create the graph

    // beacon for camera and light  
    OSG::NodePtr b1n = OSG::Node::create();
    OSG::GroupPtr b1 = OSG::Group::create();
    OSG::beginEditCP(b1n);
    b1n->setCore( b1 );
    OSG::endEditCP(b1n);

    // transformation
    OSG::NodePtr t1n = OSG::Node::create();
    OSG::TransformPtr t1 = OSG::Transform::create();
    OSG::beginEditCP(t1n);
    t1n->setCore( t1 );
    t1n->addChild( b1n );
    OSG::endEditCP(t1n);

    cam_trans = t1;

    // light
    
    OSG::NodePtr dlight = OSG::Node::create();
    
    dl = OSG::DirectionalLight::create();

    OSG::beginEditCP(dlight);
    dlight->setCore( dl );
    OSG::endEditCP(dlight);
    
    OSG::beginEditCP(dl);
    dl->setAmbient( .3, .3, .3, 1 );
    dl->setDiffuse( 1, 1, 1, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);
    OSG::endEditCP(dl);

    // root
    root = OSG::Node::create();
    OSG::GroupPtr gr1 = OSG::Group::create();
    OSG::beginEditCP(root);
    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );
    OSG::endEditCP(root);

    // Load the file


//    OSG::VRMLFile *pLoader = new OSG::VRMLFile();

//    pLoader->scanStandardPrototypes("std.wrl", 0);

    for(OSG::UInt32 numFiles = 1; numFiles < OSG::UInt32(argc); numFiles++)
    {
//        file = FhsFile::load(argv[numFiles]);

        file = OSG::SceneFileHandler::the().read(argv[numFiles], 0);

/*
        pLoader->scanFile(argv[numFiles], OSG::VRMLFile::CreateNormals);

        file = pLoader->getRoot();
        */
                     
        OSG::beginEditCP(dlight);
        dlight->addChild( file );
        dlight->invalidateVolume();
        OSG::endEditCP(dlight);
    }


    dlight->updateVolume();

    // should check first. ok for now.
    const OSG::BoxVolume *vol = (OSG::BoxVolume *)&dlight->getVolume();
        
    OSG::Vec3f min,max;
    vol->getBounds( min, max );
    
    std::cout << "Volume: from " << min << " to " << max << std::endl;

//  std::cerr << "Tree: " << std::endl;
//    root->print();

    // Camera
    OSG::PerspectiveCameraPtr cam = OSG::PerspectiveCamera::create();

    cam->setBeacon( b1n );
    cam->setFov( OSG::deg2rad( 60 ) );
    cam->setNear( 0.1 );
    cam->setFar( 5000 );

    // Solid Background
    OSG::SolidBackgroundPtr bkgnd = OSG::SolidBackground::create();
    bkgnd->setColor( OSG::Color3f(0,0,1) );

    // Viewport

    OSG::ViewportPtr vp = OSG::Viewport::create();
    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );

    // Window
    std::cout << "GLUT winid: " << winid << std::endl;

    OSG::GLUTWindowPtr gwin;

    GLint glvp[4];
    glGetIntegerv( GL_VIEWPORT, glvp );

    gwin = OSG::GLUTWindow::create();
    gwin->setId(winid);
    gwin->setSize( glvp[2], glvp[3] );

    win = gwin;

    win->addPort( vp );

    // Action
    
    ract = OSG::RenderAction::create();

    std::cerr << "Calculating normals...";
    
    // Task 1: Cal Vertex Normals
//  ract->registerEnterFunction( OSG::Geometry::getClassType(),
//                                  OSG::osgFunctionFunctor2( calcVNormal ) );
    
//  ract->apply( dlight );

    std::cerr << "done." << std::endl;
 
    // tball
    
    OSG::Vec3f pos(min[0] + ((max[0] - min[0]) * 0.5), 
                   min[1] + ((max[1] - min[1]) * 0.5), 
                   max[2] + ( max[2] - min[2] ) * 1.5 );

    OSG::Vec3f cpos(min[0] + ((max[0] - min[0]) * 0.5), 
                    min[1] + ((max[1] - min[1]) * 0.5), 
                    min[2] + ((max[2] - min[2]) * 0.5) );

    float scale = (max[2] - min[2] + max[1] - min[1] + max[0] - min[0]) / 6;

    tball.setMode( OSG::Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( OSG::Trackball::OSGFree );
    tball.setRotationCenter  (cpos);
    tball.setTranslationScale(scale);

    cam->setFar(fabs(max[2] + ( max[2] - min[2] ) * 3));
 
    if(fabs(max[2] + ( max[2] - min[2] ) * 3) > 1000.f)
    {
        cam->setNear(10);
    }

    // run...
    
    glutMainLoop();

    
    return 0;
}


