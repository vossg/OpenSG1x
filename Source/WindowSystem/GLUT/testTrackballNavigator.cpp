/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

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
#include <OSGDrawAction.h>
#include <OSGSimpleGeometry.h>
#include <OSGSceneFileHandler.h>

#include <OSGDirectionalLight.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGGLUTWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
//#include "OSGUniformBackground.h"

#include "OSGSceneFileHandler.h"

#include "OSGNavigator.h"


/**---added stuff------------------------------------------------------------------*/

/**---end of added stuff-----------------------------------------------------------*/

using namespace OSG;

DrawAction * ract;

NodePtr  root;

NodePtr  file;

PerspectiveCameraPtr cam;
ViewportPtr vp;
WindowPtr win;

TransformPtr cam_trans;

Navigator trackball;

int mouseb = 0;
int lastx=0, lasty=0;

bool buttonPressed;

void
display(void)
{
    Matrix m1, m2, m3;

    m1=trackball.getMatrix();
//    m1.transpose();

//    m2.setTranslate(0,0,8);
//    m1.mult(m2);

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
/*  Real32 w = win->getWidth(), h = win->getHeight();


    Real32  a = 2. * ( lastx / w - .5 ),
                b = 2. * ( .5 - lasty / h ),
                c = 2. * ( x / w - .5 ),
                d = 2. * ( .5 - y / h );

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
    }*/
    lastx = x;
    lasty = y;

    if ( buttonPressed ) trackball.moveTo(x,y);


}

void
mouse(int button, int state, int x, int y)
{
    if ( state == 0 )
    {
        switch ( button )
        {
        case GLUT_LEFT_BUTTON:  trackball.buttonPress(Navigator::LEFT_MOUSE,x,y);
                                break;
        case GLUT_MIDDLE_BUTTON:trackball.buttonPress(Navigator::MIDDLE_MOUSE,x,y);
                                break;
        case GLUT_RIGHT_BUTTON: trackball.buttonPress(Navigator::RIGHT_MOUSE,x,y);
                                break;
        }
        mouseb |= 1 << button;
        buttonPressed=true;
    }
    else if ( state == 1 )
    {
        switch ( button )
        {
        case GLUT_LEFT_BUTTON:  trackball.buttonRelease(Navigator::LEFT_MOUSE,x,y);
                                break;
        case GLUT_MIDDLE_BUTTON:trackball.buttonRelease(Navigator::MIDDLE_MOUSE,x,y);
                                break;
        case GLUT_RIGHT_BUTTON: trackball.buttonRelease(Navigator::RIGHT_MOUSE,x,y);
                                break;
        }
        mouseb &= ~(1 << button);
        buttonPressed=false;
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
        case 'r':   std::cerr << "Sending ray through " << x << "," << y << std::endl;
            Line l;
            cam->calcViewRay( l, x, y, *vp );
            std::cerr << "From " << l.getPosition() << ", dir " << l.getDirection() << std::endl;
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
    glutIdleFunc(display);
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

    NodePtr file = NullFC;

    if ( argc > 1 )
        file = SceneFileHandler::the().read(argv[1]);

    if ( file == NullFC )
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        //file = makeTorus( .5, 2, 16, 16 );
        file = makeBox( 2,4,6, 1,1,1 );
    }

    file->updateVolume();

    Vec3f min,max;
    file->getVolume().getBounds( min, max );

    std::cout << "Volume: from " << min << " to " << max << std::endl;

    NodePtr file2=makeBox(2,4,6,1,1,1);

    beginEditCP(dlight);
    dlight->addChild( file );
    dlight->addChild( file2 );
    endEditCP(dlight);

    std::cerr << "Tree: " << std::endl;
//  root->dump();

    // Camera

    cam = PerspectiveCamera::create();
    cam->setBeacon( b1n );
    cam->setFov( deg2rad( 90 ) );
    cam->setNear( 0.1 );
    cam->setFar( 10000 );

    // Background
    SolidBackgroundPtr bkgnd = SolidBackground::create();

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

    trackball.setMode(Navigator::TRACKBALL);

    trackball.setViewport(vp);

    // run...

    glutMainLoop();

    return 0;
}

