/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

// Minimalistic OpenSG program

// GLUT is used for window handling
#include <OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OSGConfig.h>

// The GLUT-OpenSG connection class
#include <OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OSGSimpleSceneManager.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OSGSimpleGeometry.h>


#include <OSGSceneFileHandler.h>
#include <OSGAction.h>
#include <OSGGraphOpSeq.h>
#include <OSGMergeGraphOp.h>
#include <OSGSplitGraphOp.h>
#include <OSGVerifyGeoGraphOp.h>
#include <OSGGraphOpFactory.h>
#include <OSGComponentTransform.h>
#include <OSGDirectionalLight.h>
#include <OSGSpotLight.h>
#include <OSGLight.h>
#include <OSGPointLight.h>
#include <OSGSwitch.h>
#include <OSGDistanceLOD.h>
#include <OSGBillboard.h>
#include <OSGMaterialGroup.h>
//#include <OSGConsistencyTools.h>

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGThread.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGChangeList.h>
#include <OSGFieldContainer.h>
#include <OSGGroup.h>
#include <OSGFieldContainerPtr.h>
#include <OSGSimpleAttachments.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

NodePtr scene;

// Standard GLUT callback functions
void display( void )
{
    mgr->idle();
    mgr->redraw();
}

void reshape( int w, int h )
{
    mgr->resize( w, h );
    glutPostRedisplay();
}

void
motion(int x, int y)
{
    mgr->mouseMove( x, y );
    glutPostRedisplay();
}

void
mouse(int button, int state, int x, int y)
{
    if ( state )
        mgr->mouseButtonRelease( button, x, y );
    else
        mgr->mouseButtonPress( button, x, y );
    glutPostRedisplay();
}

void
key(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:    exit(1);
    case 'a':   mgr->setHighlight( scene );
                break;
    case 's':   mgr->setHighlight( NullFC );
                break;
    case 'l':   mgr->useOpenSGLogo();
                break;
    case 'f':   mgr->setNavigationMode(Navigator::FLY);
                break;
    case 't':   mgr->setNavigationMode(Navigator::TRACKBALL);
                break;
    case 'x':   mgr->getNavigator()->set(
                    Pnt3f(0,0,2),Pnt3f(0,0,0),Vec3f(0,1,0));
                break;
    case 'c':   mgr->getNavigator()->set(
                    Pnt3f(0,0,2),Pnt3f(2,2,1),Vec3f(0,1,0));
                break;
    }
    mgr->key(key,x,y);
    glutPostRedisplay();
}


// Initialize GLUT & OpenSG and set up the scene
int main (int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(key);
    glutIdleFunc(display);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // create the scene

    NodePtr sc;
    
    if(argc < 2)
    {
        sc = makeBox(2,2,1,3,2,1);
    }
    else
    {
        sc = SceneFileHandler::the().read(argv[1]);
    }
    NodePtr scene=Node::create();
    GroupPtr grp=Group::create();
    beginEditCP(scene);
    scene->setCore(grp);
    scene->addChild(sc);
    endEditCP(scene);
    
    GraphOpSeq gos;
    MergeGraphOp mgo;    
    SplitGraphOp sgo;
    VerifyGeoGraphOp vggo;
    GraphOpFactory::the().registerOp(&mgo);
    GraphOpFactory::the().registerOp(&sgo);
    GraphOpFactory::the().registerOp(&vggo);

    gos.setGraphOps("Exclude(Me,You) Verify(true) AddExclude(Us,Them) Merge() Exclude(All) Split(1500)");

    //gos.addGraphOp(&vggo);
    //gos.addGraphOp(&mgo);
    //gos.addGraphOp(&sgo);

    if (gos.run(scene))
        printf("GraphOpSeq finished successfully\n");
    else
        printf("GraphOpSeq failed\n");
    
    printf("starting simple scene manager\n");
    mgr = new SimpleSceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );
    mgr->setStatistics(true);

    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}
